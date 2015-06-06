cmake_minimum_required(VERSION 3.2)
project(watch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(watch ${SOURCE_FILES} Watcher.cpp Watcher.h)
target_link_libraries(watch pthread)