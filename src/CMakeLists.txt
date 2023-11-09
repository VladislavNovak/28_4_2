cmake_minimum_required(VERSION 3.26)

add_executable(
        28_4_2
        ../main.cpp
        utilities.cpp
        Station.cpp
        Train.cpp
        ../headers/constants.h
        ../headers/utilities.h
        ../headers/Station.h
        ../headers/Train.h
)

target_include_directories(28_4_2 PUBLIC ${CMAKE_SOURCE_DIR}/headers)