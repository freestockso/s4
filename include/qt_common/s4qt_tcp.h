#pragma once

#include "network/tcp_client.h"
#include "network/tcp_server.h"

#include <QWidget>

namespace S4{
namespace QT{

class qt_tcp_json_client : public QWidget, public S4::NW::tcp_json_client_t
{
    Q_OBJECT
public:
    explicit qt_tcp_json_client(const std::string& port) :
        tcp_json_client_t(port)
    {};

    virtual void onRecv(const json_ptr_t& pJ) override
    {
        emit signal_onRecv(pJ);
        json_ptr_t pJ_read;
        read(pJ_read);  //pop
    };
signals:
    void signal_onRecv(const std::shared_ptr<nlohmann::json>&);
};

}
}