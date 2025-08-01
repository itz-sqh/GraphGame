#pragma once
#include "NetworkMessage.h"


class Session;

class NetworkObserver {
public:
    virtual ~NetworkObserver() = default;

    virtual void onMessageReceived(std::shared_ptr<Session> session,
                                   const NetworkMessage &message) = 0;

    virtual void onClientConnected(std::shared_ptr<Session> session) = 0;

    virtual void onClientDisconnected(std::shared_ptr<Session> session) = 0;
};
