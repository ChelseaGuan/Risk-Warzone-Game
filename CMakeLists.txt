cmake_minimum_required(VERSION 3.17)
project(Risk-Warzone-Game)

set(CMAKE_CXX_STANDARD 20)
include_directories(src/Source_Files)
include_directories(src/Header_Files)
set(SOURCE_FILES src/Source_Files/Map.cpp src/Source_Files/MapLoader.cpp src/Source_Files/Player.cpp src/Source_Files/Orders.cpp src/Source_Files/Cards.cpp src/Source_Files/GameEngine.cpp src/Source_Files/GameObservers.cpp src/Source_Files/PlayerStrategies.cpp)
add_executable(A3Part01 ${SOURCE_FILES} src/Assignment3_drivers/part1.cpp)
add_executable(A3Part02 ${SOURCE_FILES} src/Assignment3_drivers/part2.cpp)