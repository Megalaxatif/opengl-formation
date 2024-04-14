cmake_minimum_required(VERSION 3.27)

project(formation-openGL)

add_executable(Prog src/main.cpp src/glad.c)

target_include_directories(Prog PUBLIC include)

target_link_directories(Prog PRIVATE lib)

target_link_libraries(Prog glfw3)