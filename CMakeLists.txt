cmake_minimum_required(VERSION 3.0.0)
project(Simulation VERSION 0.1.0)


set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -fsanitize=address")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}")
find_package(raylib)
add_executable(Simulation src/main.c src/cloth.c)
target_link_libraries(Simulation raylib)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})