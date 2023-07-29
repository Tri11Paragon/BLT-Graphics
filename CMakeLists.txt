cmake_minimum_required(VERSION 3.0)
project(BLT_GRAPHICS VERSION 0.0.1)

option(ENABLE_ADDRSAN "Enable the address sanitizer" OFF)
option(ENABLE_UBSAN "Enable the ub sanitizer" OFF)
option(ENABLE_TSAN "Enable the thread data race sanitizer" OFF)

set(CMAKE_CXX_STANDARD 20)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)

add_subdirectory(libraries/BLT)
add_subdirectory(libraries/glfw)

set(OLD_CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE "Release")
set(ASSIMP_INSTALL OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
set(ASSIMP_BUILD_TESTS OFF)

add_subdirectory(libraries/assimp)
set(CMAKE_BUILD_TYPE ${OLD_CMAKE_BUILD_TYPE})

include_directories(include/)

file(GLOB_RECURSE source_files src/*.cpp)

add_executable(BLT_GRAPHICS ${source_files})

target_link_libraries(BLT_GRAPHICS PUBLIC glfw)
target_link_libraries(BLT_GRAPHICS PUBLIC BLT)
target_link_libraries(BLT_GRAPHICS PUBLIC OpenGL)
target_link_libraries(BLT_GRAPHICS PUBLIC assimp)
target_compile_options(BLT_GRAPHICS PRIVATE -Wall -Wextra -Wpedantic)

if (${ENABLE_ADDRSAN} MATCHES ON)
    target_compile_options(BLT_GRAPHICS PRIVATE -fsanitize=address)
    target_link_options(BLT_GRAPHICS PRIVATE -fsanitize=address)
endif ()

if (${ENABLE_UBSAN} MATCHES ON)
    target_compile_options(BLT_GRAPHICS PRIVATE -fsanitize=undefined)
    target_link_options(BLT_GRAPHICS PRIVATE -fsanitize=undefined)
endif ()

if (${ENABLE_TSAN} MATCHES ON)
    target_compile_options(BLT_GRAPHICS PRIVATE -fsanitize=thread)
    target_link_options(BLT_GRAPHICS PRIVATE -fsanitize=thread)
endif ()
