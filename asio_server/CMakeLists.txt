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
project(asio_server LANGUAGES CXX)

# 查找 Boost 的 filesystem 和 system 库
# find_package(Boost  REQUIRED COMPONENTS filesystem system)
find_package(asio CONFIG REQUIRED)
  # 不指定 COMPONENTS   头文件-only的 Asio库

add_executable(asio_server asio_server.cpp)

# set(asio_INCLUDE_DIRS "/path/to/asio/include")
# set(asio_LIBRARY_DIRS "/path/to/asio/lib")

target_include_directories(asio_server PRIVATE ${asio_INCLUDE_DIRS})

target_link_libraries(asio_server PRIVATE asio::asio)    


  # # this is heuristically generated, and may not be correct                                             
  # find_package(asio CONFIG REQUIRED)                                                                    
  # target_link_libraries(main PRIVATE asio::asio) 

  # asio provides CMake targets:                                                                            
                                                                                                        
  # # this is heuristically generated, and may not be correct                                             
  # find_package(asio CONFIG REQUIRED)                                                                    
  # target_link_libraries(main PRIVATE asio::asio)  