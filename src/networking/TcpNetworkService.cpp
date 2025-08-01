#include"networking/TcpNetworkService.h"


TcpNetworkService::TcpNetworkService(boost::asio::io_context &ioContext, uint16_t port) : ctx(ctx),
    acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v6(), port)) {
    acceptor.set_option(boost::asio::ip::v6_only(false));
    acceptor.set_option(boost::asio::socket_base::reuse_address(true));
}

TcpNetworkService::~TcpNetworkService() {
    TcpNetworkService::stop();
}

void TcpNetworkService::start() {
    acceptConnection();
}

void TcpNetworkService::stop() {
    boost::system::error_code ec;
    acceptor.close(ec);
    if (ec) {
        std::cerr << "Error while closing acceptor: " << ec.message() << std::endl;
    }

    for (auto &session: sessions) {
        session->send(NetworkMessage());
    }
    sessions.clear();
}

void TcpNetworkService::acceptConnection() {
    acceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (ec) {
                std::cerr << "Accept error: " << ec.message() << std::endl;
            } else {
                auto session = std::make_shared<Session>(std::move(socket));
            }
            acceptConnection();
        });
}

void TcpNetworkService::setupSession(std::shared_ptr<Session> session) {
    sessions.insert(session);
    session->start(
        [this, session](const NetworkMessage &msg) {
            for (auto *observer: observers) {
                observer->onMessageReceived(session, msg);
            }
        },
        [this,session]() {
            sessions.erase(session);
            for (auto *observer: observers)
                observer->onClientDisconnected(session);
        });
    for (auto *observer: observers) {
        observer->onClientConnected(session);
    }
}

void TcpNetworkService::broadcast(const NetworkMessage &msg) {
    for (auto &session: sessions)
        sendTo(session, msg);
}

void TcpNetworkService::sendTo(std::shared_ptr<Session> session, const NetworkMessage& message) {
    if (session && sessions.contains(session)) {
        session->send(message);
    }
}

void TcpNetworkService::registerObserver(NetworkObserver* observer) {
    observers.push_back(observer);
}

void TcpNetworkService::unregisterObserver(NetworkObserver* observer) {
    observers.erase(std::ranges::remove(observers, observer).begin(), observers.end());
}

size_t TcpNetworkService::clientCount() const {
    return sessions.size();
}

uint16_t TcpNetworkService::port() const {
    return acceptor.local_endpoint().port();
}

