###############################
# P1Charts configuration file #
###############################

cmake_minimum_required (VERSION 2.8)
project(P1Charts)

#SET (CMAKE_C_COMPILER "${DEVROOT}/usr/bin/clang")

message(STATUS "Make C flags used: ${CMAKE_C_FLAGS}")

include_directories ("${PROJECT_SOURCE_DIR}/drawing")
add_subdirectory (drawing)

include_directories ("${PROJECT_SOURCE_DIR}/drawing/storage")
#add_subdirectory (storage)

add_executable(grapsGen main.c ./drawing/drawing.c)
target_link_libraries (grapsGen Drawing)
