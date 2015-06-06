cmake_minimum_required(VERSION 2.8.7)
project(WatchCpp)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Using Clang with libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libstdc++")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

include_directories(src)

message("Compilers: ${CMAKE_CXX_COMPILER} ${CMAKE_C_COMPILER}")
add_library(watch src/Watcher.cpp src/Watcher.h)
target_link_libraries(watch pthread)

enable_testing()
add_executable(test_watch_file test/integration/test_watch_file.cpp)
target_link_libraries(test_watch_file watch)
add_test(test_watch_file test_watch_file)
