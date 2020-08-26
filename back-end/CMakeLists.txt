cmake_minimum_required(VERSION 3.9)
project(backend)

find_package(cpprestsdk REQUIRED)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE cpprestsdk::cpprest)