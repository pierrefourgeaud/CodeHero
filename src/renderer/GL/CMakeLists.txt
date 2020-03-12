cmake_minimum_required (VERSION 3.9)

project (CodeHero.Renderer.OpenGL)

# ---------- GLFW ----------
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (${VENDORS_PATH}/glfw vendors/glfw)

add_subdirectory (${VENDORS_PATH}/glad vendors/glad)

set (RENDERER_PATH ${SRCS_PATH}/renderer)

set (SOURCES
     ${RENDERER_PATH}/GL/RendererGL.cpp
     ${RENDERER_PATH}/GL/RendererGLModule.cpp
     ${RENDERER_PATH}/GL/Utils.cpp
     ${RENDERER_PATH}/GL/WindowGL.cpp
)

set (HEADERS
     ${RENDERER_PATH}/Renderer.h
     ${RENDERER_PATH}/Window.h
     ${RENDERER_PATH}/GL/RendererGL.h
     ${RENDERER_PATH}/GL/RendererGLModule.h
     ${RENDERER_PATH}/GL/Utils.h
     ${RENDERER_PATH}/GL/WindowGL.h
)

include_directories (
  ${SRCS_PATH}
  ${VENDORS_PATH}/glfw/include/

  ${GLAD_INCLUDE_DIRS}
)

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES} ${HEADERS})

add_definitions (-DGLFW_INCLUDE_NONE
                 -DMODULE_NAME="Renderer.OpenGL")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} CodeHero.Core)
add_dependencies (${PROJECT_NAME} CodeHero.Dummy)
