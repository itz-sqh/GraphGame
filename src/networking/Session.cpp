#include"networking/Session.h"


constexpr size_t maxMessageSize = 2 << 10;

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket(std::move(socket)) {
}

void Session::start(MessageHandler messageHandler, ErrorHandler errorHandler) {
    this->messageHandler = std::move(messageHandler);
    this->errorHandler = std::move(errorHandler);
    asyncReadHeader();
}


void Session::asyncReadHeader() {
    auto self(shared_from_this());
    buf.resize(sizeof(uint32_t));
    boost::asio::async_read(socket, boost::asio::buffer(buf),
                            [this, self](boost::system::error_code ec, size_t /*len*/) {
                                if (ec) {
                                    handleError();
                                    return;
                                }
                                messageSize = ntohl(*reinterpret_cast<uint32_t *>(buf.data()));
                                if (messageSize > maxMessageSize) {
                                    handleError();
                                    return;
                                }
                                asyncReadBody();
                            });
}
void Session::asyncReadBody() {
    auto self(shared_from_this());
    buf.resize(messageSize);
    boost::asio::async_read(socket, boost::asio::buffer(buf),
        [this,self](boost::system::error_code ec, size_t /*len*/) {
            if (ec) {
                handleError();
                return;
            }
            processMessage();
            asyncReadHeader();
        });

}


void Session::processMessage() {
    try {
        NetworkMessage msg = MessageSerializer::deserialize(buf);
        if (messageHandler) {
            messageHandler(msg);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error while processing message: " << e.what() << std::endl;
        handleError();
    }
}

void Session::send(const NetworkMessage &message) {
    auto self(shared_from_this());
    std::string data = MessageSerializer::serialize(message);
    writeQueue.push(std::move(data));
    if (writeQueue.size() == 1) {
        asyncWrite();
    }
}

void Session::asyncWrite() {
    auto self(shared_from_this());
    const std::string &data = writeQueue.front();

    uint32_t size = htonl(static_cast<uint32_t>(data.size()));

    std::vector<boost::asio::const_buffer> bufs;

    bufs.push_back(boost::asio::buffer(&size, sizeof(size)));
    bufs.push_back(boost::asio::buffer(data));

    boost::asio::async_write(socket, bufs,
                             [this,self](boost::system::error_code ec, size_t /*len*/) {
                                 if (ec) {
                                     handleError();
                                     return;
                                 }
                                 writeQueue.pop();
                                 if (!writeQueue.empty())
                                     asyncWrite();
                             });
}

void Session::handleError() {
    if (errorHandler)
        errorHandler();
}

boost::asio::ip::tcp::endpoint Session::endpoint() const {
    return socket.remote_endpoint();
}