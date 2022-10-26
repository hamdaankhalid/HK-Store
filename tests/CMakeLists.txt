cmake_minimum_required(VERSION 3.21)

set(SOURCES
  logger-tests.cpp
)

add_executable(home_server_traffic_dashboard_tests ${SOURCES})

target_link_libraries(
  home_server_traffic_dashboard_tests PUBLIC
  gtest_main
  logger
)

add_test(NAME home_server_traffic_dashboard_tests COMMAND home_server_traffic_dashboard_tests)
