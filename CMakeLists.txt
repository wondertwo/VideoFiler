cmake_minimum_required(VERSION 3.13)
set(PROJECT_VIDEO_FILER videofiler)
project(${PROJECT_VIDEO_FILER})
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_SOURCE_FILES
        main.cc
        moretools.cc
        moretools.h
        cronet_builder.cc
        cronet_builder.h
        wake_reference.cc
        wake_reference.h
        cmd_parameters.cc
        cmd_parameters.h
)

add_executable(${PROJECT_VIDEO_FILER} ${PROJECT_SOURCE_FILES})

# https://github.com/fmtlib/fmt
# https://github.com/nlohmann/json