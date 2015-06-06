cmake_minimum_required(VERSION 2.8.7)
project(watch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src)

add_library(watch src/Watcher.cpp src/Watcher.h)
target_link_libraries(watch pthread)

add_executable(test_watch_file test/integration/test_watch_file.cpp)
target_link_libraries(test_watch_file watch)
enable_testing()
add_test(test_watch_file test_watch_file)
