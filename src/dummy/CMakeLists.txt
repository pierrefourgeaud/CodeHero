cmake_minimum_required (VERSION 3.9)

project (CodeHero.Dummy)

set (DUMMY_PATH ${SRCS_PATH}/dummy)

set (SOURCES
     ${DUMMY_PATH}/DummyModule.cpp
)

set (HEADERS
     ${DUMMY_PATH}/DummyModule.h
)

include_directories (
  ${SRCS_PATH}
)

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES} ${HEADERS})

add_definitions (-DMODULE_NAME="Dummy")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} CodeHero.Core)
