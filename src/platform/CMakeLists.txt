cmake_minimum_required (VERSION 3.9)

project (CodeHero.Platform)

set (PLATFORM_PATH ${SRCS_PATH}/platform)

set (SOURCES
    ${PLATFORM_PATH}/PlatformModule.cpp
)

set (HEADERS
    ${PLATFORM_PATH}/PlatformModule.h

    ${PLATFORM_PATH}/IPlatformWindow.h
    ${PLATFORM_PATH}/HAL/PlatformWindow.h
)

include_directories (
  ${SRCS_PATH}
)

# Platforms
# Windows
if (WIN32)
    set (SOURCES ${SOURCES}
        ${PLATFORM_PATH}/Windows/WindowsPlatformWindow.cpp
    )

    set (HEADERS ${HEADERS}
        ${PLATFORM_PATH}/Windows/WindowsPlatformWindow.h
    )
endif (WIN32)
# /Windows
# /Platforms

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

add_definitions (-DMODULE_NAME="Platform")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} CodeHero.Core)
