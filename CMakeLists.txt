cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

file(COPY src/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Asteroids src/main.cpp src/direction.cpp src/asteroid.cpp src/point.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/ship.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Asteroids ${SDL2_LIBRARIES} pthread)
