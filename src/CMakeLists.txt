cmake_minimum_required(VERSION 3.21)

set(SOURCES
  main.cpp
)

add_executable(home_server_traffic_dashboard_tests ${SOURCES})

target_link_libraries(
  home_server_traffic_dashboard PUBLIC
  filepoller
  logger
)
