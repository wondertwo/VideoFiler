cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
project(videofiler)

add_executable(videofiler
        main.cpp
        mtools.cpp
        mtools.h
        cronet_builder.cpp
        cronet_builder.h
        wake_reference.cpp
        wake_reference.h

#        videotool/video_format_parser.cpp
#        videotool/video_format_parser.h
#        videotool/base_box.cpp
#        videotool/base_box.h
#        videotool/box_factory.cpp
#        videotool/box_factory.h
#        videotool/mp4file.cpp
#        videotool/mp4file.h


)