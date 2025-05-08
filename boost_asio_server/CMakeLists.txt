
cmake_minimum_required(VERSION 3.10)
project(boost_server LANGUAGES CXX)

add_executable(boost_server boost_server.cpp)

find_package(Boost REQUIRED)  # 不指定 COMPONENTS   头文件-only的 Boost 库
# find_package(Boost  REQUIRED COMPONENTS filesystem system)


target_link_libraries(boost_server PRIVATE Boost::boost)
# target_link_libraries(server PRIVATE Boost::filesystem Boost::system)
