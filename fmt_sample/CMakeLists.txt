cmake_minimum_required(VERSION 3.20)


project(FmtExample)


# 查找 fmt 库
find_package(fmt REQUIRED)

# 添加可执行文件
add_executable(fmt fmt.cpp)


target_include_directories(fmt PRIVATE ${fmt_INCLUDE_DIRS})

# 链接 fmt 库
target_link_libraries(fmt PRIVATE fmt::fmt)



# The package fmt provides CMake targets:                                                                 
                                                                                                        
#     find_package(fmt CONFIG REQUIRED)                                                                   
#     target_link_libraries(main PRIVATE fmt::fmt)                                                        
                                                                                                        
#     # Or use the header-only version                                                                    
#     find_package(fmt CONFIG REQUIRED)                                                                   
#     target_link_libraries(main PRIVATE fmt::fmt-header-only)