#include <fmt/core.h>

int main() {
    // 使用fmt库打印格式化字符串
    fmt::print("Hello, {}!\n", "world");

    // 打印整数和浮点数
    int number = 4321;
    double pi = 4.14159555555;
    fmt::print("Number: {}, Pi: {:.5f}\n", number, pi);

    return 0;
}