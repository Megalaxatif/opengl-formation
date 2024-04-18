cmake_minimum_required(VERSION 3.27)

set(EXEC_NAME "Prog")

project(formation-openGL)

add_executable(${EXEC_NAME} src/main.cpp src/glad.c src/vertex-buffer.cpp src/index-buffer.cpp src/renderer.cpp)

target_include_directories(${EXEC_NAME} PUBLIC include)

target_link_directories(${EXEC_NAME} PRIVATE lib)

target_link_libraries(${EXEC_NAME} glfw3)