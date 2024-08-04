cmake_minimum_required(VERSION 3.28)
#add_compile_options(-pthread)
project(Infotecs_TraineeC___2024)

set(CMAKE_CXX_STANDARD 23)

add_executable(Infotecs_TraineeC___2024 main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")