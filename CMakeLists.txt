cmake_minimum_required(VERSION 3.5.0)
project(learnopengl VERSION 0.1.0 LANGUAGES C CXX)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("lib/glfw")
find_package(OpenGL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(learnopengl ${all_SRCS})
target_link_libraries(learnopengl glfw)
target_link_libraries(learnopengl OpenGL::GL)