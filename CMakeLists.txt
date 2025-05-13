cmake_minimum_required(VERSION 3.16)
project(SunnyEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source directories
set(ENGINE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/engine/src")
set(APP_SOURCE_DIR "${CMAKE_SOURCE_DIR}/app/src")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find dependencies
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

#------------------SunnyEngine------------------
# Set Source Files
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS ${ENGINE_SOURCE_DIR}/*.cpp)

# Ceate Static library
add_library(SunnyEngine STATIC ${ENGINE_SOURCES})

target_include_directories(SunnyEngine PUBLIC ${ENGINE_SOURCE_DIR}/headers)

# Compiler flags for the engine
target_compile_options(SunnyEngine PRIVATE -Wall -Wextra -O2)

# Installaion
include(GNUInstallDirs)

 
install(TARGETS SunnyEngine
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION include
)

install(DIRECTORY ${ENGINE_SOURCE_DIR}/headers
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SunnyEngine
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
)

# Package configuration
install(EXPORT SunnyEngineTargets
    FILE SunnyEngineTargets.cmake
    NAMESPACE SunnyEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SunnyEngine
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SunnyEngineConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SunnyEngineConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SunnyEngine
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SunnyEngineConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SunnyEngineConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SunnyEngineConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SunnyEngine
)

#------------------Simulation-------------------
# Set Source Files
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS ${APP_SOURCE_DIR}/*.cpp)

# Ceate Executable
add_executable(Simulation ${APP_SOURCES})

# Add headers
target_include_directories(
    Simulation PRIVATE 
    ${APP_SOURCE_DIR}/headers
)

# Link simulation with Engine and sdl3
target_link_libraries(Simulation PRIVATE
    SunnyEngine
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
)

# Compile options
target_compile_options(Simulation PRIVATE -Wall -Wextra -O2)

#cmake -B build
#cmake --build build
#cmake --install build --prefix ~/.local
