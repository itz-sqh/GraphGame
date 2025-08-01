#pragma once
#include "NetworkService.h"
#include "Session.h"
#include <unordered_set>
#include <boost/asio.hpp>
#include<iostream>
#include "networking/NetworkObserver.h"

class TcpNetworkService : public NetworkService {
public:
    TcpNetworkService(boost::asio::io_context &ioContext, uint16_t port);

    ~TcpNetworkService();

    void start() override;

    void stop() override;

    void broadcast(const NetworkMessage &msg) override;

    void sendTo(std::shared_ptr<Session> session,
                const NetworkMessage &message) override;

    void registerObserver(NetworkObserver *observer) override;

    void unregisterObserver(NetworkObserver *observer) override;

    size_t clientCount() const override;

    uint16_t port() const override;

private:
    void acceptConnection();

    void setupSession(std::shared_ptr<Session> session);

    void notifyObservers(void (NetworkObserver::*method)(std::shared_ptr<Session>));

    boost::asio::io_context &ctx;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_set<std::shared_ptr<Session> > sessions;
    std::vector<NetworkObserver *> observers;
};
