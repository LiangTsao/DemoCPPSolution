# CMakeList.txt: DemoProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 指定 vcpkg 工具链文件
#set(CMAKE_TOOLCHAIN_FILE "E:/work/gitee/vcpkg/scripts/buildsystems/vcpkg.cmake")
#find_package(openssl REQUIRED)  
# 自动搜索 installed/x64-windows/share/openssl/

# 添加 Asio 的 include 路径
# include_directories("F:/asio-1.30.2/include")
# include_directories("F:/boost_1_88_0")

# # 添加 Boost.Asio 的库路径
# link_directories("F:/boost_1_88_0/libs")


cmake_minimum_required(VERSION 3.10)
project(boost_server LANGUAGES CXX)

# 查找 Boost 的 filesystem 和 system 库
# find_package(Boost  REQUIRED COMPONENTS filesystem system)
find_package(Boost REQUIRED)  # 不指定 COMPONENTS   头文件-only的 Boost 库

add_executable(boost_server boost_server.cpp)

# 链接 Boost 库（Modern CMake 目标模式）
target_include_directories(boost_server PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(boost_server PRIVATE Boost::boost)

# target_link_libraries(server PRIVATE Boost::filesystem Boost::system)
