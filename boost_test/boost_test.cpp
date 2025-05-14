#include <coroutine>
#include <iostream>
#include <thread>
#include <future>

// 自定义 awaitable 类型
class MyAwaitable {
public:
    // 重载 operator co_await，返回 awaiter 对象
    auto operator co_await() const {
        struct Awaiter {
            bool await_ready() const noexcept {
                std::cout << "await_ready() called\n";
                return false; // 总是暂停协程
            }
            
            void await_suspend(std::coroutine_handle<> handle) const noexcept {
                std::cout << "await_suspend() called\n";
                // 模拟异步操作，在另一个线程中延迟执行
                std::thread([handle]() {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "Resuming coroutine after delay\n";
                    handle.resume(); // 恢复协程执行
                }).detach();
            }
            
            int await_resume() const noexcept {
                std::cout << "await_resume() called\n";
                return 42; // 返回结果给 co_await 表达式
            }
        };
        
        return Awaiter{};
    }
};

// 协程函数
std::coroutine_handle<> coroutineHandle;

struct Task {
    struct promise_type {
        Task get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task coroutineFunction() {
    std::cout << "Coroutine started\n";
    int result = co_await MyAwaitable{};
    std::cout << "Coroutine resumed with result: " << result << "\n";
}

int main() {
    std::cout << "Main: Starting coroutine\n";
    coroutineFunction();
    std::cout << "Main: Coroutine launched, continuing...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}