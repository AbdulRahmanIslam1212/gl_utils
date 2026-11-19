cmake_minimum_required(VERSION 3.16)
project(gl_utils VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(OpenGL REQUIRED)

add_library(gl_utils
    src/gl_utils.cpp
    third_party/glad/src/gl.c
)
add_library(gl_utils::gl_utils ALIAS gl_utils)

target_include_directories(gl_utils
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(gl_utils
    PUBLIC
        OpenGL::GL
        ${CMAKE_DL_LIBS}
)

install(TARGETS gl_utils
    EXPORT gl_utilsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/gl_utils
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/gl
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/KHR
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/gl_utilsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/gl_utilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/gl_utilsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gl_utils
)

install(EXPORT gl_utilsTargets
    FILE gl_utilsTargets.cmake
    NAMESPACE gl_utils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gl_utils
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/gl_utilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/gl_utilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gl_utils
)
