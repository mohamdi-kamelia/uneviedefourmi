cmake_minimum_required(VERSION 3.10)
project(uneviedefourmi)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(uneviedefourmi
    main.cpp
    src/ants.cpp
)
