cmake_minimum_required(VERSION 3.26)

add_executable(
        28_4_2
        ../main.cpp
        Station.cpp
        utilities.cpp
        ../headers/Station.h
        ../headers/utilities.h
        Train.cpp
        ../headers/Train.h
)

target_include_directories(28_4_2 PUBLIC ${CMAKE_SOURCE_DIR}/headers)