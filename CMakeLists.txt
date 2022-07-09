cmake_minimum_required(VERSION 3.16)
project(sokolMiniPrj VERSION 1.0)

add_executable(${PROJECT_NAME} src/main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")
set(CMAKE_CXX_FLAGS "-stdlib=libc++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -v -Wall -Wextra -Wno-long-long -pedantic -fno-exceptions -fno-rtti -lpthread -lm")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Og -g")

target_include_directories(${PROJECT_NAME} PUBLIC
                            "${CMAKE_SOURCE_DIR}/src"
                            "${CMAKE_SOURCE_DIR}/lib"
                            )

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()