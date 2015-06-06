cmake_minimum_required(VERSION 2.8.7)
project(watch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

include_directories(src)
set(SOURCE_FILES test/integration/main.cpp)

add_executable(watch ${SOURCE_FILES} src/Watcher.cpp src/Watcher.h)

enable_testing()
add_test(integrationtest watch)
target_link_libraries(watch pthread)