#pragma once
#include "NetworkMessage.h"
#include <memory>
#include <boost/asio.hpp>

class NetworkObserver;
class Session;

class NetworkService {
public:
    virtual ~NetworkService() = default;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void broadcast(const NetworkMessage &message) = 0;

    virtual void sendTo(std::shared_ptr<Session> session,
                        const NetworkMessage &message) = 0;

    virtual void registerObserver(NetworkObserver *observer) = 0;

    virtual void unregisterObserver(NetworkObserver *observer) = 0;

    virtual size_t clientCount() const = 0;

    virtual uint16_t port() const = 0;
};
