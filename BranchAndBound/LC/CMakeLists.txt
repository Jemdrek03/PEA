cmake_minimum_required(VERSION 3.28)
project(PEA_LC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(PEA_LC LC_Main.cpp
        ConfigFile.h
        DataReader.h
        DataSaver.h
        DataReader.cpp
        DataSaver.cpp
        LC.cpp
        LC.h
        Generate.cpp
        Generate.h)
