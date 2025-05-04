# CMakeList.txt: DemoProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

#set(CMAKE_TOOLCHAIN_FILE "E:/work/gitee/vcpkg/scripts/buildsystems/vcpkg.cmake")
#find_package(openssl REQUIRED)  
# 自动搜索 installed/x64-windows/share/openssl/

# 将源代码添加到此项目的可执行文件。
add_executable (DemoProject "DemoProject.cpp" "DemoProject.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DemoProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
