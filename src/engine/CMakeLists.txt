cmake_minimum_required (VERSION 3.9)

project (CodeHero.Engine)

set (ENGINE_PATH ${SRCS_PATH}/engine)

set (SOURCES
     ${ENGINE_PATH}/EngineLoop.cpp
)

set (HEADERS
    ${ENGINE_PATH}/EngineAPI.h
    ${ENGINE_PATH}/EngineLoop.h
)

include_directories (
    ${SRCS_PATH}
)

add_definitions (-DENGINE_API_EXPORT -DMODULE_NAME="Engine")

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES} ${HEADERS})

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} CodeHero.Core)
add_dependencies (${PROJECT_NAME} CodeHero.Renderer.OpenGL)
