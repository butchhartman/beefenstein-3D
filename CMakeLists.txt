cmake_minimum_required(VERSION 3.8)

project(SDLbase)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_executable(${PROJECT_NAME} "src/SDLbase.c" "include/SDLbase.h")

add_subdirectory("vendored/SDL3")
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendored/SDL3/include/SDL3")