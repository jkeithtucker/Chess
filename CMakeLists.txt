cmake_minimum_required (VERSION 3.8)

project ("ChessProject")

install(CODE [[
  message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
  message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
  message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
]])

set(SFML_DIR "C:/dev/libraries/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS "system" "window" "graphics" CONFIG REQUIRED)

add_executable (ChessProject "app.cpp" "app.hpp" "bitboards.cpp" "bitboards.hpp" "chess.cpp" "chess.hpp" "fen.cpp" "fen.hpp" "main.cpp" "pch.cpp" "pch.hpp" "window.cpp" "window.hpp" "chessConst.hpp")

target_link_libraries(ChessProject PRIVATE "sfml-system" "sfml-graphics" "sfml-window")