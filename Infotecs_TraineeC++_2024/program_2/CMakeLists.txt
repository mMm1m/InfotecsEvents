cmake_minimum_required(VERSION 3.25.1)
project(program_2)

#include_directories(../common)

set(CMAKE_CXX_STANDARD 11)

add_executable(program_2 main.cpp NetworkServer.cpp DataHandler.cpp )

#target_link_libraries(program_2 network)
#target_link_libraries(output_server PRIVATE common)