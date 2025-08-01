#pragma once
#include "NetworkMessage.h"
#include <memory>
#include <queue>
#include <functional>
#include <boost/asio.hpp>
#include<iostream>

class Session : public std::enable_shared_from_this<Session> {
public:
    using MessageHandler = std::function<void(const NetworkMessage &)>;
    using ErrorHandler = std::function<void()>;

    explicit Session(boost::asio::ip::tcp::socket socket);

    void start(MessageHandler messageHandler,
               ErrorHandler errorHandler);

    void send(const NetworkMessage &message);

    boost::asio::ip::tcp::endpoint endpoint() const;

private:
    void asyncReadHeader();

    void asyncReadBody();

    void processMessage();

    void asyncWrite();

    void handleError();

    boost::asio::ip::tcp::socket socket;
    uint32_t messageSize = 0;
    std::string buf;
    std::queue<std::string> writeQueue;
    MessageHandler messageHandler;
    ErrorHandler errorHandler;
};
