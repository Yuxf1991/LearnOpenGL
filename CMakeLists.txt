cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 14)

set(BUILD_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_PATH}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_PATH}/lib)

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)
set(RESOURCE_PATH ${PROJECT_SOURCE_DIR}/resources)
set(GLFW_PATH ${SOURCE_PATH}/ThirdParty/glfw-3.3)
set(GLAD_PATH ${SOURCE_PATH}/ThirdParty/glad)

include_directories(${SOURCE_PATH} ${GLFW_PATH}/include ${GLAD_PATH}/include)
link_directories(${GLFW_PATH}/lib-mingw-w64)

INSTALL(DIRECTORY ${RESOURCE_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)

link_libraries(glfw3)

aux_source_directory(${SOURCE_PATH}/utils UTILS_SRC)
aux_source_directory(${GLAD_PATH}/src GLAD_SRC)
set(SRC_LIST ${GLAD_SRC} ${UTILS_SRC})

# Chapter1: getting started
set(Chapter1_PATH ${SOURCE_PATH}/Chapter1)
add_executable(helloWindow ${Chapter1_PATH}/helloWindow/main.cpp ${SRC_LIST})
add_executable(helloTriangle1 ${Chapter1_PATH}/helloTriangle/triangle1.cpp ${SRC_LIST})