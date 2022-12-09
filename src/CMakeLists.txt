cmake_minimum_required(VERSION 3.8)

project(Terremotos)

set(CMAKE_C_STANDARD 17)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c17")

set(EXECUTABLE_OUTPUT_PATH "bin")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(Servidor Servidor.c)

add_executable(Cliente Cliente.c)
