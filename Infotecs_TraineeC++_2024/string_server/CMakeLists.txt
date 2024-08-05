cmake_minimum_required(VERSION 3.25.1)
add_compile_options(-pthread)
project(string_server)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(string_server main.cpp)
#find_package(Boost REQUIRED)
#target_link_libraries(your_program_executable Boost::Boost)
#target_link_libraries(string_server PRIVATE common)
