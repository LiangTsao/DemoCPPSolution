cmake_minimum_required(VERSION 3.10)
project(asio_server LANGUAGES CXX)

add_executable(asio_server asio_server.cpp)

                                          
find_package(asio CONFIG REQUIRED)                                                                    
target_link_libraries(asio_server PRIVATE asio::asio) 

