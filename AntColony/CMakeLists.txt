cmake_minimum_required(VERSION 3.28)
project(AntColony)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")

configure_file(resources/config.txt config.txt COPYONLY)
configure_file(resources/data.txt data.txt COPYONLY)


add_executable(AntColony main.cpp
        ConfigFile.h
        DataReader.cpp
        DataReader.h
        DataSaver.h
        DataSaver.cpp
        AntSearch.cpp
        AntSearch.h
        testing.cpp
        testing.h)
