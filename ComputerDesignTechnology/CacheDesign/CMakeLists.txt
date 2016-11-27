cmake_minimum_required(VERSION 3.3)
project(mp1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    cache.cpp
    cache.h
    castTypes.h
    main.h
    sim_cache.cpp)

add_executable(mp1 ${SOURCE_FILES})