# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.20)

# 如果支持，请为 MSVC 编译器启用热重载。
# if (POLICY CMP0141)
#   cmake_policy(SET CMP0141 NEW)
#   set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
# endif()

#CMAKE_TOOLCHAIN_FILE通常在项目命令之前设置，因为它会影响整个项目的配置，包括编译器和查找路径
# 在CMakeLists.txt的最顶部，调用project()之前，使用set命令来定义CMAKE_TOOLCHAIN_FILE
# set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")


project ("DemoSolution" LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含子项目。
add_subdirectory ("DemoProject")
add_subdirectory ("FooProject")
add_subdirectory ("BarProject")
add_subdirectory ("boost_asio_server")
add_subdirectory ("asio_server")
add_subdirectory ("fmt_sample")

