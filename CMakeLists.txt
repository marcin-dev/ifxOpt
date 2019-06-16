cmake_minimum_required (VERSION 2.6)

project (ifxOpt)

add_compile_options(--std=c++11)

#add_executable(ifxOpt ifxOpt.cpp)
add_subdirectory(src)
add_subdirectory(test)
