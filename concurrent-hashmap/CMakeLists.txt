set (HEADER_LIST_CM "${HkStorageEngine_SOURCE_DIR}/concurrent-hashmap/include/concurrent-hashmap.hpp")

add_library(concurrent_hashmap STATIC src/concurrent-hashmap.cpp ${HEADER_LIST_CM})

target_include_directories(concurrent_hashmap PUBLIC ./include)

target_compile_features(concurrent_hashmap PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/concurrent-hashmap/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST_CM}
)
