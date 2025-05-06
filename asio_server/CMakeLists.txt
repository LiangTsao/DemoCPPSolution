# CMakeList.txt: DemoProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 指定 vcpkg 工具链文件
#set(CMAKE_TOOLCHAIN_FILE "E:/work/gitee/vcpkg/scripts/buildsystems/vcpkg.cmake")
#find_package(openssl REQUIRED)  
# 自动搜索 installed/x64-windows/share/openssl/

# 添加 Asio 的 include 路径
include_directories("F:/asio-1.30.2/include")
include_directories("F:/boost_1_88_0")

# 添加 Boost.Asio 的库路径
link_directories("F:/boost_1_88_0/libs")

# 将源代码添加到此项目的可执行文件。
add_executable (server "server.cpp" )

#target_link_libraries(server PRIVATE boost)

# TODO: 如有需要，请添加测试并安装目标。
