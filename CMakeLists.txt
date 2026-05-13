cmake_minimum_required(VERSION 3.30)
project(smartLocker)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(smartLocker
    communication.cpp
    communication.h
    config.h
    hardware.cpp
    hardware.h
    smartLocker.ino
        config.h)
