cmake_minimum_required(VERSION 3.21)

set(SOURCES
  main.cpp
)

add_executable(hk_db ${SOURCES})

target_link_libraries(
  hk_db PUBLIC
  db_server
  persistence
)

target_compile_features(hk_db PUBLIC cxx_std_17)
