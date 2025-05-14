
cmake_minimum_required(VERSION 3.10)
project(boost_test LANGUAGES CXX)

add_executable(boost_test boost_test.cpp)

find_package(Boost REQUIRED COMPONENTS  core )  # 不指定 COMPONENTS   头文件-only的 Boost 库
# find_package(Boost  REQUIRED COMPONENTS filesystem system)


target_link_libraries(boost_test PRIVATE Boost::boost Boost::core )
# # target_link_libraries(server PRIVATE Boost::filesystem Boost::system)



# # 包含 Boost 头文件目录
#  target_include_directories(boost_test PUBLIC ${Boost_INCLUDE_DIRS})
# # 链接 Boost.Core 库
# target_link_libraries(boost_test ${Boost_LIBRARIES})