cmake_minimum_required(VERSION 3.28)
project(TabuSearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(TabuSearch main.cpp
        DataReader.cpp
        DataReader.h
        DataSaver.cpp
        DataSaver.h
        Generate.cpp
        Generate.h
        ConfigFile.h
        TabuSearch.cpp
        TabuSearch.h
        NN.cpp
        NN.h
        testing.cpp
        testing.h)
