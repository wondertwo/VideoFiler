cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
project(videofiler)

add_executable(videofiler
        main.cpp
        cronet_builder.cpp
        cronet_builder.h
        wake_reference.cpp
        wake_reference.h
        video_format_parser.cpp
        video_format_parser.h
        mtools.cpp
        mtools.h
)