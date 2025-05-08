cmake_minimum_required(VERSION 3.20)


project(FmtExample)

add_executable(fmt fmt.cpp)


# The package fmt provides CMake targets:                                                                 
# find_package(fmt CONFIG REQUIRED)                                                                   
# target_link_libraries(fmt PRIVATE fmt::fmt)                                                        


# Or use the header-only version                                                                    
find_package(fmt CONFIG REQUIRED)                                                                   
target_link_libraries(fmt PRIVATE fmt::fmt-header-only)