cmake_minimum_required(VERSION 3.15)
project(programm_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(programm_2 main.cpp NetworkServer.cpp DataHandler.cpp )

target_include_directories(programm_2 PRIVATE ${CMAKE_SOURCE_DIR}/common)