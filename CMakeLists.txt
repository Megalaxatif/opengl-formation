cmake_minimum_required(VERSION 3.27)

set(EXEC_NAME "Prog")

file(GLOB SRC_FILES "src/*.cpp")
file(GLOB IMGUI_FILES "src/imgui/*.cpp")
file(GLOB GLAD_FILE "src/glad.c")



project(formation-openGL)

add_executable(${EXEC_NAME} ${SRC_FILES} ${IMGUI_FILES} ${GLAD_FILE})

target_include_directories(${EXEC_NAME} PUBLIC include src/header)

target_link_directories(${EXEC_NAME} PRIVATE lib)

target_link_libraries(${EXEC_NAME} glfw3 libstbi.a)