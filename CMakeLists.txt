cmake_minimum_required(VERSION 3.8)
project(md5Crack)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES serial.c serial.c)
add_executable(md5Crack ${SOURCE_FILES})
target_link_libraries(md5Crack crypto)