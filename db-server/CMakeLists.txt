set (HEADER_LIST "${HkStorageEngine_SOURCE_DIR}/db-server/include/db-server.hpp")

add_library(db_server STATIC src/db-server.cpp ${HEADER_LIST})

target_link_libraries(
  db_server PUBLIC 
  logger
  concurrent_hashmap
)

target_include_directories(db_server PUBLIC ./include)

target_compile_features(db_server PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/db-server/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
