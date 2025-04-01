cmake_minimum_required(VERSION 3.28)
project(PEA)

set(CMAKE_CXX_STANDARD 17)
set(CMake_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA BruteMain.cpp
        ConfigFile.h
        bruteforce.cpp
        bruteforce.h
        DataReader.cpp
        DataSaver.cpp
        DataReader.h
        DataSaver.h
        Generate.h
        Generate.cpp
)
