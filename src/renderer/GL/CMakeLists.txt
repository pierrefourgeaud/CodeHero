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
)

set (HEADERS
     ${RENDERER_PATH}/Renderer.h
     ${RENDERER_PATH}/GL/RendererGL.h
     ${RENDERER_PATH}/GL/RendererGLModule.h

     # Core
     ${SRCS_PATH}/core/logger/Logger.h
     ${SRCS_PATH}/core/TypeDefs.h

)

include_directories (
  ${SRCS_PATH}
  ${VENDORS_PATH}/glfw/include/

  ${GLAD_INCLUDE_DIRS}
)

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES} ${HEADERS})

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES} ${ADDITIONAL_LIBRARIES})
