#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <iostream>

namespace asio = boost::asio;
using namespace asio::experimental::awaitable_operators;

asio::awaitable<void> async_task() {
    asio::steady_timer timer(co_await asio::this_coro::executor, std::chrono::milliseconds(100));
    co_await timer.async_wait(asio::use_awaitable);
    std::cout << "Timer 1 done" << std::endl;

    timer.expires_after(std::chrono::milliseconds(100));
    co_await timer.async_wait(asio::use_awaitable);
    std::cout << "Timer 2 done" << std::endl;
}

int main() {
    asio::io_context ctx;
    asio::co_spawn(ctx, async_task(), asio::detached);
    ctx.run();
    return 0;
}