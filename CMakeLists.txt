cmake_minimum_required(VERSION 3.13.0)
project(ComputerGraphicsExercise)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src
        src/include
        thirdparty
        thirdparty/assimp/include
        thirdparty/glfw/include
        thirdparty/googletest
        thirdparty/glm
        thirdparty/stb)

add_subdirectory(src)
add_subdirectory(thirdparty/assimp)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/googletest)

