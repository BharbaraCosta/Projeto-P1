##################################
# Drawing lib configuration file #
##################################

cmake_minimum_required (VERSION 2.6)
#SET (CMAKE_C_COMPILER "${DEVROOT}/usr/bin/clang")

message("AQUI ${PROJECT_SOURCE_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/drawing/storage")
add_subdirectory (storage)

add_library(Drawing SHARED drawing.c)
target_link_libraries (Drawing m)
target_link_libraries (Drawing cairo)
target_link_libraries (Drawing Storage)

#add_executable(test drawing.c drawingTest.c)
#target_link_libraries (test cairo)
#target_link_libraries (test Storage)

