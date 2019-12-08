cmake_minimum_required(VERSION 3.15)
project(algorithm_impl)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-D_DEBUG)

include_directories(common)
include_directories(hamilton_circuit)
include_directories(dfs)
include_directories(dijkstra)

add_executable(algorithm_impl
        main.cpp
        hamilton_circuit/hamilton.cpp
        hamilton_circuit/hamilton.h
        common/data_struct.cpp
        common/data_struct.h
        common/logger.cpp
        common/logger.h
        dijkstra/dijkstra.cpp
        dijkstra/dijkstra.h dfs/dfs.cpp dfs/dfs.h)

link_libraries(algorithm_impl pthread)
