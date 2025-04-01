cmake_minimum_required(VERSION 3.28)
project(PEA_NN)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA_NN
        ConfigFile.h
        DataReader.h
        DataSaver.h
        DataReader.cpp
        DataSaver.cpp
        NN.h
        NN.cpp
        NN_Main.cpp
        Generate.cpp
        Generate.h)
