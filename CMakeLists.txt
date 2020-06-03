cmake_minimum_required(VERSION 3.13)
project(babymonster)

set(CMAKE_CXX_STANDARD 11)

add_executable(babymonster main.cpp
        common/cronet_builder.cpp
        common/cronet_builder.h common/wake_reference.cpp common/wake_reference.h common/video_format_parser.cpp common/video_format_parser.h)
