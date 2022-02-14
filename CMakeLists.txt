cmake_minimum_required(VERSION 3.11.3)
project(conc4)

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

# Find all executables
file(GLOB project_SRCS *.cpp *.h) #src/*.h

# Add project executable
add_executable(conc4 ${project_SRCS})
