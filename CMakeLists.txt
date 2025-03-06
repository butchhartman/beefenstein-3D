cmake_minimum_required(VERSION 3.8)

project(SDLbase)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_executable(${PROJECT_NAME} "src/SDLbase.c" "include/SDLbase.h")

if("vendored/SDL3/CMakeLists.txt")
	# SDL3 files already exist, use them
	# add_subdirectory("vendored/SDL3")
else()
	#SDl3 files do not exist, clone them.
	execute_process(COMMAND git submodule update --init --recursive)
#	add_custom_target(generate_vendored ALL COMMAND git submodule update --init -- vendored/SDL3 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#	add_dependencies(${PROJECT_NAME} generate_vendored)
endif()
add_subdirectory("vendored/SDL3")

target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendored/SDL3/include/SDL3")