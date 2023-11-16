cmake_minimum_required(VERSION 3.26)

add_executable(
        28_4_2
        ../main.cpp
        ../headers/constants.h
        ../headers/utilities.h
        ../headers/Station.h
        ../headers/Train.h
        ../headers/threads.h
        utilities.cpp
        Station.cpp
        Train.cpp
        threads.cpp
)

target_include_directories(28_4_2 PUBLIC ${CMAKE_SOURCE_DIR}/headers)