#include <fmt/core.h>

int main() {
    // 使用fmt库打印格式化字符串
    fmt::print("Hello, {}!\n", "world");

    // 打印整数和浮点数
    int number = 42;
    double pi = 3.14159;
    fmt::print("Number: {}, Pi: {:.2f}\n", number, pi);

    return 0;
}