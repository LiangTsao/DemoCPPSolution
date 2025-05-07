#include <iostream>
#include <memory>
#include <string>
#include <asio.hpp>
#include <iomanip>

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        do_read();
    }

private:
    void do_read() {
        auto self(shared_from_this());
        std::cout << "[Session] Waiting to read data..." << std::endl;
        socket_.async_read_some(asio::buffer(data_, max_length),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "[Session] Received data: " << std::string(data_, length) << " (" << length << " bytes)" << std::endl;
                    do_write(length);
                } else {
                    std::cerr << "[Session] Read error: " << ec.message() << std::endl;
                }
            });
    }

    void do_write(std::size_t length) {
        auto self(shared_from_this());
        std::cout << "[Session] Sending data back to client..." << std::endl;
        asio::async_write(socket_, asio::buffer(data_, length),
            [this, self](std::error_code ec, std::size_t /*length*/) {
                if (!ec) {
                    std::cout << "[Session] Data sent successfully." << std::endl;
                    do_read();
                } else {
                    std::cerr << "[Session] Write error: " << ec.message() << std::endl;
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class Server {
public:
    Server(asio::io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    void do_accept() {
        std::cout << "[Server] Waiting for new connections..." << std::endl;
        acceptor_.async_accept(
            [this](std::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::cout << "[Server] New connection established from: " << socket.remote_endpoint() << std::endl;
                    std::make_shared<Session>(std::move(socket))->start();
                } else {
                    std::cerr << "[Server] Accept error: " << ec.message() << std::endl;
                }
                do_accept();
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
    try {
        short port = 4321; // Default port
        if (argc == 2) {
            port = std::atoi(argv[1]);
        } else if (argc > 2) {
            std::cerr << "[Server] Usage: server [port]\n";
            return 1;
        }

        std::cout << "[Server] Starting server on port: " << port << std::endl;
        asio::io_context io_context;

        Server server(io_context, port);

        std::cout << "[Server] Server is running. Waiting for connections..." << std::endl;
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "[Server] Exception: " << e.what() << "\n";
    }

    return 0;
}