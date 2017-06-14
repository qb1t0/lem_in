cmake_minimum_required(VERSION 3.7)
project(lem_in)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c lem_in.h)
add_executable(lem_in ${SOURCE_FILES})
target_link_libraries(lem_in ${CMAKE_SOURCE_DIR}/libft/libft.a)