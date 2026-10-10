# d3d9.dll proxy for the original game (32-bit, separate from the main build):
#   cmake -S tools/re/d3d9proxy -B build/d3d9proxy -G "Visual Studio 17 2022" -A Win32
#   cmake --build build/d3d9proxy --config Release
cmake_minimum_required(VERSION 3.28)
project(opprobe_d3d9 CXX)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
	message(FATAL_ERROR "The game is 32-bit: configure with -A Win32")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_library(d3d9proxy SHARED d3d9proxy.cpp gamecontrol.cpp gamecontrol.hpp d3d9.def)
target_link_libraries(d3d9proxy PRIVATE dxguid)
set_target_properties(d3d9proxy PROPERTIES OUTPUT_NAME d3d9 CXX_STANDARD 20)
target_compile_options(d3d9proxy PRIVATE /W4)
