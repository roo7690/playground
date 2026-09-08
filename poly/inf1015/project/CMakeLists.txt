cmake_minimum_required(VERSION 3.16)

project(Chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt6_DIR "/home/roo7690/opt/Qt/6.11.0/gcc_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Quick)

set(CMAKE_AUTOMOC ON)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.hpp")
file(GLOB_RECURSE ASSETS images/*.png)

foreach(file ${ASSETS})
    file(RELATIVE_PATH relPath
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${file}
    )

    set_source_files_properties(${file}
        PROPERTIES QT_RESOURCE_ALIAS ${relPath}
    )
endforeach()

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(chess
  main.cpp
)

qt_add_qml_module(chess
  URI Chess
  QML_FILES Main.qml
  RESOURCES ${ASSETS}
)

target_sources(chess PRIVATE
  ${SOURCES}
  ${HEADERS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(chess PROPERTIES
# MACOSX_BUNDLE_GUI_IDENTIFIER com.example.chess
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(chess
  PRIVATE Qt6::Quick
)

install(TARGETS chess
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
