cmake_minimum_required(VERSION 3.16)
project(pfpf VERSION 1.0)

set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -v -Wall -Wextra -Wno-long-long -pedantic -fno-exceptions -fno-rtti -lpthread -lm")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Og -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# from https://github.com/floooh/cimgui-sokol-starterkit/blob/main/CMakeLists.txt

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

#=== LIBRARY: sokol
# add headers to the the file list because they are useful to have in IDEs
set(SOKOL_HEADERS
    lib/sokol/sokol_gfx.h
    lib/sokol/sokol_app.h
    lib/sokol/sokol_glue.h)
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    add_library(sokol STATIC ${SOKOL_HEADERS})
    target_compile_options(sokol PRIVATE -x objective-c)
    target_link_libraries(sokol PUBLIC
        "-framework QuartzCore"
        "-framework Cocoa"
        "-framework MetalKit"
        "-framework Metal")
else()
    add_library(sokol STATIC ${SOKOL_HEADERS})
    if (CMAKE_SYSTEM_NAME STREQUAL Linux)
        target_link_libraries(sokol INTERFACE X11 Xi Xcursor GL dl m)
        target_link_libraries(sokol PUBLIC Threads::Threads)
    endif()
endif()
target_include_directories(sokol INTERFACE lib/sokol)

# thuwerato
add_library(thuwerato INTERFACE)
target_include_directories(thuwerato INTERFACE lib/thuwerato)

#=== EXECUTABLE: 
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_executable(${PROJECT_NAME} WIN32 src/main.cpp)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
else()
    add_executable(${PROJECT_NAME} src/main.cpp)
endif()
set_target_properties(sokol PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} sokol thuwerato)

# Emscripten-specific linker options
if (CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # use our own minimal shell.html
    # target_link_options(${PROJECT_NAME} PRIVATE --shell-file ../sokol/shell.html)
    # WASM+JS size optimizations
    target_link_options(${PROJECT_NAME} PRIVATE -sNO_FILESYSTEM=1 -sASSERTIONS=0 -sMALLOC=emmalloc --closure=1)
endif()

# explicitly strip dead code
if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    target_link_options(${PROJECT_NAME} PRIVATE LINKER:-dead_strip)
endif()

# this hack removes the xxx-CMakeForceLinker.cxx dummy file
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)