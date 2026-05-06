cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME labs2_7_server)
project("${PROJECT_NAME}")
set(CMAKE_CXX_STANDARD 20)

add_executable("${PROJECT_NAME}" server.cpp)