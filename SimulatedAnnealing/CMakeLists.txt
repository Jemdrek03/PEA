cmake_minimum_required(VERSION 3.28)
project(SimulatedAnnealingop)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimulatedAnnealingop main.cpp
        ConfigFile.h
        DataReader.cpp
        DataSaver.cpp
        SimulatedAnnealing.h
        SimulatedAnnealing.cpp
        NN.h
        NN.cpp
        Generate.h
        Generate.cpp
        testing.cpp
        testing.h)
