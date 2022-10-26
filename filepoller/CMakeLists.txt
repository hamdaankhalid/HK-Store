set (HEADER_LIST "${HomeServerTrafficDashboard_SOURCE_DIR}/filepoller/include/filepoller.hpp")

add_library(filepoller STATIC src/filepoller.cpp ${HEADER_LIST})

target_include_directories(filepoller PUBLIC ./include)

target_compile_features(filepoller PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/filepoller/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
