#include "network/tcp_client.h"

namespace S4{
namespace NW{

chat_client::chat_client(asio::io_context &io_context,
                          const tcp::resolver::results_type &endpoints,
                          std::weak_ptr<tcp_json_client_t> pHoster)
    : io_context_(io_context),
      socket_(io_context),
      _connected(false),
      _connecting(true),
      _pHoster(pHoster)
{
  do_connect(endpoints);
}

bool chat_client::connectiong()
{
  return _connecting;
}

bool chat_client::connected()
{
  return _connected;
}

void chat_client::write(const chat_message &msg)
{
  asio::post(io_context_,
              [this, msg]() {
                bool write_in_progress = !write_msgs_.empty();
                write_msgs_.push_back(msg);
                if (!write_in_progress)
                {
                  do_write();
                }
              });
}

bool chat_client::read(json_ptr_t &pJ)
{
  Locker l(_mux);
  if (!_recv_msgs.size())
    return false;

  pJ = _recv_msgs.front();
  _recv_msgs.pop_front();
  return true;
}

void chat_client::close()
{
  asio::post(io_context_, [this]() {
    socket_.close();
    _connected = false;
  });
}

void chat_client::do_connect(const tcp::resolver::results_type &endpoints)
{
  _connecting = true;
  asio::async_connect(socket_, endpoints,
                      [this](std::error_code ec, tcp::endpoint) {
                        if (!ec)
                        {
                          _connected = true;
                          _connecting = false;
                          do_read_header();
                        }
                        else
                        {
                          _connected = false;
                          _connecting = false;
                        }
                      });
}

void chat_client::do_read_header()
{
  asio::async_read(socket_,
                    asio::buffer(read_msg_.data(), chat_message::header_length),
                    [this](std::error_code ec, std::size_t /*length*/) {
                      if (!ec && read_msg_.decode_header())
                      {
                        do_read_body();
                      }
                      else
                      {
                        socket_.close();
                        _connected = false;
                      }
                    });
}

void chat_client::do_read_body()
{
  asio::async_read(socket_,
                    asio::buffer(read_msg_.body(), read_msg_.body_length()),
                    [this](std::error_code ec, std::size_t /*length*/) {
                      if (!ec)
                      {
                        // std::string s(read_msg_.body(), read_msg_.body_length());

                        // int bgn, end, err;
                        // if(searchJson(s, bgn, end, &err)){
                        //   s = s.substr(bgn, end-bgn+1);
                        //   json_ptr_t pJ = std::make_shared<json>(json::parse(s));
                        //   {
                        //     Locker l(_mux);
                        //     _recv_msgs.emplace_back(pJ);
                        //   }
                        // }

                        json_ptr_t pJ = read_msg_.body_json();
                        if( pJ ){
                            Locker l(_mux);
                            _recv_msgs.push_back(pJ);
                            if (_pHoster.use_count()) {
                                std::shared_ptr<tcp_json_client_t> pH = _pHoster.lock();
                                pH->onRecv(pJ);
                            }
                        }

                        do_read_header();
                      }
                      else
                      {
                        socket_.close();
                        _connected = false;
                      }
                    });
}

void chat_client::do_write()
{
  asio::async_write(socket_,
                    asio::buffer(write_msgs_.front().data(),
                                  write_msgs_.front().length()),
                    [this](std::error_code ec, std::size_t /*length*/) {
                      if (!ec)
                      {
                        write_msgs_.pop_front();
                        if (!write_msgs_.empty())
                        {
                          do_write();
                        }
                      }
                      else
                      {
                        socket_.close();
                        _connected = false;
                      }
                    });
}

tcp_json_client_t::tcp_json_client_t(const std::string &port)
{
  tcp::resolver resolver(io_context);
  endpoints = resolver.resolve("127.0.0.1", port);
}

bool tcp_json_client_t::read(json_ptr_t &pJ)
{
  return _cc->read(pJ);
}

bool tcp_json_client_t::write(json_ptr_t pJ)
{
  if (!_cc || !_cc->connected())
  {
    return false;
  }

  std::string s = pJ->dump();
  if (s.size() > chat_message::max_body_length)
  {
    throw network_Error("json str out of length");
  }

  chat_message msg;
  msg.body_length(s.size());
  std::memcpy(msg.body(), s.c_str(), s.size());
  msg.encode_header();
  _cc->write(msg);

  return true;
}

bool tcp_json_client_t::stop()
{
  _cc->close();
  return thread_runner_t::stop();
}

bool tcp_json_client_t::main_run_loop_act(int *ec)
{
  if (ec != nullptr)
  {
    *ec = 0;
  }
  if (!_cc || (!_cc->connectiong() && !_cc->connected()))
  {
    _cc = std::make_shared<chat_client>(io_context, endpoints, shared_from_this());
  }
  io_context.run();

  return true;
}

} // namespace NW
} // namespace S4
