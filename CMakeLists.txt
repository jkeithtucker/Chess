cmake_minimum_required (VERSION 3.8)
project ("ChessApplication" VERSION 1.0.0 LANGUAGES CXX)

# Default to release builds
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

find_package(SFML 2.6.1 COMPONENTS "system" "window" "graphics" CONFIG REQUIRED)

file(GLOB SOURCES *.cpp)
add_executable (${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "assets" "lib/Release" "lib/Debug")
set(SFML_LIBS "sfml-system" "sfml-graphics" "sfml-window")
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBS})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Copy library .dlls to .exe DIR
if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
    file(COPY "lib/Debug" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(CMAKE_BUILD_TYPE STREQUAL RELEASE)
    file(COPY "lib/Release" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
