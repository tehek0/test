cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME labs2_3_main)
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)

add_executable("${PROJECT_NAME}" main.cpp car.cpp)

target_link_libraries("${PROJECT_NAME}" PRIVATE lib)