##################################
# Storage lib configuration file #
##################################

cmake_minimum_required (VERSION 2.6)
#SET (CMAKE_C_COMPILER "${DEVROOT}/usr/bin/clang")

add_library(Storage SHARED storage.c)
target_link_libraries (Storage jansson)

add_executable(storageTest storageTest.c storage.c)
target_link_libraries (storageTest jansson)
