cmake_minimum_required(VERSION 3.15)
add_compile_options(-pthread)
project(programm_1)

add_executable(programm_1 main.cpp InputHandler.cpp
        DataProcessor.cpp
        NetworkClient.cpp
        ThreadsExecutor.cpp
)

target_include_directories(programm_1 PRIVATE ${CMAKE_SOURCE_DIR}/common)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
