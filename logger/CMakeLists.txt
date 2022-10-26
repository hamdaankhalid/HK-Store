set (HEADER_LIST "${HomeServerTrafficDashboard_SOURCE_DIR}/logger/include/logger.hpp")

add_library(logger STATIC src/logger.cpp ${HEADER_LIST})

target_include_directories(logger PUBLIC ./include)

target_compile_features(logger PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/logger/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
