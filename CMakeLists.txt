cmake_minimum_required(VERSION 3.14)
project(ColisionSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files here
add_executable(ColisionSimulation ./src/main.cpp)

# Optionally, add include directories
target_include_directories(ColisionSimulation PRIVATE include)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Optionally, link libraries
target_link_libraries(ColisionSimulation PRIVATE sfml-graphics sfml-window sfml-system)