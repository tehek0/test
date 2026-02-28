cmake_minimum_required(VERSION 3.15) 

set(PROJECT_NAME labs2_3_lib) 			 
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_library("${PROJECT_NAME}" STATIC inc/workshop.h src/workshop.cpp)
target_include_directories("${PROJECT_NAME}" PUBLIC inc)