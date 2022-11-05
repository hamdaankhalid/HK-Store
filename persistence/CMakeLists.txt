set (HEADER_LIST "${HkStorageEngine_SOURCE_DIR}/persistence/include/persistence.hpp")

add_library(persistence STATIC src/persistence.cpp ${HEADER_LIST})

target_link_libraries(
  persistence PUBLIC 
  logger
  concurrent_hashmap
)

target_include_directories(persistence PUBLIC ./include)

target_compile_features(persistence PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/persistence/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
