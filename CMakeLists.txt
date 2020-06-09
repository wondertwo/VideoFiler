cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
project(videofiler)

add_executable(videofiler
        main.cc
        mtools.cc
        mtools.h
        cronet_builder.cc
        cronet_builder.h
        wake_reference.cc
        wake_reference.h
        cmd_parameters.cc
        cmd_parameters.h


)