#include <iostream>
#include <string>
#include <deque>
#include <memory>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read_until.hpp>

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::steady_timer;
using namespace std::chrono_literals;

// 处理单个TCP连接
awaitable<void> handle_connection(tcp::socket socket) {
    try {
        char data[1024];
        for (;;) {
            std::size_t n = co_await socket.async_read_some(
                boost::asio::buffer(data), use_awaitable);
            
            co_await boost::asio::async_write(
                socket, boost::asio::buffer(data, n), use_awaitable);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
}

// 监听TCP连接
awaitable<void> listen_for_connections(boost::asio::io_context& io_context, unsigned short port) {
    try {
        tcp::acceptor acceptor(io_context, {tcp::v4(), port});
        
        for (;;) {
            tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
            boost::asio::co_spawn(io_context, handle_connection(std::move(socket)), boost::asio::detached);
        }
    }
    catch (std::exception& e) {
        std::cerr << "Listener error: " << e.what() << std::endl;
    }
}

// 定时任务处理
awaitable<void> periodic_task(boost::asio::io_context& io_context) {
    boost::asio::steady_timer timer(io_context);
    try {
        for (int i = 1;; ++i) {
            timer.expires_after(5s);
            co_await timer.async_wait(boost::asio::use_awaitable);
            std::cout << "Periodic task executed " << i << " times" << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Timer error: " << e.what() << std::endl;
    }
}

// 信号处理
awaitable<void> signal_handler(boost::asio::io_context& io_context) {
    boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
    try {
        co_await signals.async_wait(boost::asio::use_awaitable);
        std::cout << "\nCaught signal, exiting..." << std::endl;
        io_context.stop();
    }
    catch (std::exception& e) {
        std::cerr << "Signal handler error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        
        // 启动各个协程任务
        boost::asio::co_spawn(io_context, listen_for_connections(io_context, 12345), boost::asio::detached);
        boost::asio::co_spawn(io_context, periodic_task(io_context), boost::asio::detached);
        boost::asio::co_spawn(io_context, signal_handler(io_context), boost::asio::detached);
        
        std::cout << "Server started. Listening on port 12345..." << std::endl;
        std::cout << "Press Ctrl+C to exit" << std::endl;
        
        // 运行I/O上下文
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}