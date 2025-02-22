# CMakeList.txt : CMake project for GPbase, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GPbase")

# Add source to the gl3w library to be generated 
# This step only needs to be done once to generate the library. The source file for the gl3w library has since been removed from the project.
# gl3w will need to be recompiled and added in order to generate this library again.
#add_library (gl3wlib STATIC "src/GL3W/gl3w.c")

# Add link director(y/ies) for libraries
link_directories ("lib")

# Add source to this project's executable.
add_executable (GPbase "src/GPbase.c"  "include/GPbase.h")

# Add libraries to this project's executable.
# Simply can specify the name of the library because CMake knows to look in the lib folder.
target_link_libraries (GPbase glfw3 gl3wlib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GPbase PROPERTY C_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
