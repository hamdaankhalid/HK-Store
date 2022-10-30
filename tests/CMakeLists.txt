cmake_minimum_required(VERSION 3.21)

set(SOURCES
  logger-tests.cpp
  hashmap-tests.cpp
)

add_executable(hk_storage_engine_tests ${SOURCES})

target_link_libraries(
  hk_storage_engine_tests PUBLIC
  gtest_main
  logger
  concurrent_hashmap
)

add_test(NAME hk_storage_engine_tests COMMAND hk_storage_engine_tests)
