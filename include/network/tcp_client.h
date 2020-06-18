//Base on asio:
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include "asio.hpp"
#include "chat_message.h"

#include "common/s4json_util.h"
#include "common/s4thread.h"
#include "common/s4exceptions.h"


namespace S4 {
namespace NW {

using asio::ip::tcp;

class chat_client;

class tcp_json_client_t  : public thread_runner_t
{
public:
  explicit tcp_json_client_t(const std::string& port);

  bool read(json_ptr_t& pJ);

  bool write(json_ptr_t pJ);

	virtual bool stop();

protected:
  virtual bool main_run_loop_act(int* ec = nullptr) override;
private:
    std::shared_ptr<chat_client> _c;
    asio::io_context io_context;
    tcp::resolver::results_type endpoints;
};

typedef std::deque<chat_message> chat_message_queue;
typedef std::deque<json_ptr_t> json_message_queue;
  
class chat_client
{
public:
  chat_client(asio::io_context& io_context,
      const tcp::resolver::results_type& endpoints);

  bool connectiong();

  bool connected();

  void write(const chat_message& msg);

  bool read(json_ptr_t& pJ);

  void close();

private:
  void do_connect(const tcp::resolver::results_type& endpoints);

  void do_read_header();

  void do_read_body();

  void do_write();

private:
  asio::io_context& io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;

  Mutex _mux;
  json_message_queue _recv_msgs;

  bool _connected;
  bool _connecting;

};



} // namespace NW
} // namespace S4
