cmake_minimum_required(VERSION 3.21)

project(HkStorageEngine)

enable_testing()

#### git submodule ####
add_subdirectory(googletest)
###

add_subdirectory(src)

add_subdirectory(db-server)

add_subdirectory(concurrent-hashmap)

add_subdirectory(persistence)

add_subdirectory(logger)

add_subdirectory(tests)
