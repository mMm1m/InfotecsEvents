cmake_minimum_required(VERSION 3.25.1)
add_compile_options(-pthread)
project(programm_1)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(programm_1 main.cpp InputHandler.cpp
        DataProcessor.cpp
        NetworkClient.cpp
        Worker.cpp
)
