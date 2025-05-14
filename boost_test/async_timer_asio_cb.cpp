#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;

void async_task(asio::io_context& ctx) {
    auto timer1 = std::make_shared<asio::steady_timer>(ctx, std::chrono::milliseconds(100));
    timer1->async_wait([timer1, &ctx](const boost::system::error_code& ec) {
        if (!ec) {
            std::cout << "Timer 1 done" << std::endl;

            auto timer2 = std::make_shared<asio::steady_timer>(ctx, std::chrono::milliseconds(100));
            timer2->async_wait([timer2](const boost::system::error_code& ec) {
                if (!ec) {
                    std::cout << "Timer 2 done" << std::endl;
                } else {
                    std::cerr << "Timer 2 error: " << ec.message() << std::endl;
                }
            });
        } else {
            std::cerr << "Timer 1 error: " << ec.message() << std::endl;
        }
    });
}

int main() {
    asio::io_context ctx;
    async_task(ctx);
    ctx.run();
    return 0;
}