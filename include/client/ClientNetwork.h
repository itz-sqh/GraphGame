#pragma once
#include <boost/asio/io_service.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "../common/NetworkMessage.h"

class ClientNetwork {
public:
    bool connect(const std::string& ip, unsigned short port);
    void send(const NetworkMessage& msg);
    bool poolMessage(NetworkMessage& msg);

private:
    boost::asio::io_service service;
    std::unique_ptr<boost::asio::ip::tcp::socket> socket;
    boost::asio::streambuf buf;

};
