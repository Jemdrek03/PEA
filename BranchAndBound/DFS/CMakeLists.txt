cmake_minimum_required(VERSION 3.28)
project(PEA_DFS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA_DFS DFS_Main.cpp
        ConfigFile.h
        DataReader.h
        DataSaver.h
        DFS.h
        DFS.cpp
        DataSaver.cpp
        DataReader.cpp
        Generate.h
        Generate.cpp)
