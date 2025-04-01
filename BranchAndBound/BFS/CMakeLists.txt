cmake_minimum_required(VERSION 3.28)
project(PEA_BFS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA_BFS BFS_Main.cpp
        ConfigFile.h
        DataReader.h
        DataSaver.h
        BFS.h
        DataReader.cpp
        DataSaver.cpp
        BFS.cpp
        Generate.cpp
        Generate.h
        NN.h
        NN.cpp)
