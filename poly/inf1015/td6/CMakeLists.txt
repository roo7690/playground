cmake_minimum_required(VERSION 3.16.0)

project(chess VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(Qt6_DIR "/home/roo7690/Qt6/6.11.0/gcc_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(chess src/main.cpp)

target_link_libraries(chess PRIVATE Qt6::Widgets)

file(GLOB ALL_FILES
  src/*.cpp
  src/*.hpp
)

target_compile_options(chess PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS chess RUNTIME DESTINATION bin)

qt_generate_deploy_app_script(
  TARGET chess
  FILENAME_VARIABLE deploy_script
  NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})