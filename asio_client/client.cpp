// DemoProject.cpp: 定义应用程序的入口点。
//

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        boost::asio::write(socket, boost::asio::buffer(message));

        char reply[1024];
        size_t reply_length = socket.read_some(boost::asio::buffer(reply));
        std::cout << "Reply: " << std::string(reply, reply_length) << "\n";

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
