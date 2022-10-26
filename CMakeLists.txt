cmake_minimum_required(VERSION 3.21)

project(HomeServerTrafficDashboard)

enable_testing()

#### git submodule ####
add_subdirectory(googletest)

add_subdirectory(logger)
add_subdirectory(filepoller)

# add_subdirectory(src)

add_subdirectory(tests)
