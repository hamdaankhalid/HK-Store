set (HEADER_LIST_CM "${HkStorageEngine_SOURCE_DIR}/db/include/db.hpp")

add_library(db STATIC src/db.cpp ${HEADER_LIST_CM})

target_include_directories(db PUBLIC ./include)

target_compile_features(db PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/db/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST_CM}
)
