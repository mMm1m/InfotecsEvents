cmake_minimum_required(VERSION 3.25.1)
add_compile_options(-pthread)
project(program_2)

include_directories(../common)

set(CMAKE_CXX_STANDARD 11)

add_executable(program_2 main.cpp NetworkServer.cpp DataHandler.cpp )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#target_link_libraries(output_server PRIVATE common)