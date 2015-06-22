cmake_minimum_required (VERSION 2.8)

project (SmartChess)

set (SMARTCHESS_VERSION_MAJOR 1)
set (SMARTCHESS_VERSION_MINOR 0)
set (SMARTCHESS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (SMARTCHESS_BINARY_DIR ${PROJECT_BINARY_DIR}/src)
set (SMARTCHESS_DATA_DIR ${PROJECT_BINARY_DIR}/data)


configure_file(
  "${SMARTCHESS_SOURCE_DIR}/SmartChessConfig.h.in"
  "${SMARTCHESS_BINARY_DIR}/SmartChessConfig.h"
)

include_directories ({SmartChess_BINARY_DIR})

add_subdirectory(data)
add_subdirectory(src)
