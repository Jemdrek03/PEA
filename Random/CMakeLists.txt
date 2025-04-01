cmake_minimum_required(VERSION 3.28)
project(PEA_Random)

set(CMAKE_CXX_STANDARD 17)
set(CMake_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA_Random
        ConfigFile.h
        DataReader.cpp
        DataReader.h
        DataSaver.cpp
        DataSaver.h
        Random.cpp
        Random.h
        RandomMain.cpp
        Generate.cpp
        Generate.h)
