cmake_minimum_required (VERSION 3.9)

project (CodeHero.Renderer.OpenGL)

set (RENDERER_PATH ${SRCS_PATH}/renderer)

set (SOURCES
    ${RENDERER_PATH}/GL/GLRenderer.cpp
    ${RENDERER_PATH}/GL/GLRendererModule.cpp
    ${RENDERER_PATH}/GL/GLUtils.cpp
    ${RENDERER_PATH}/GL/GLWindow.cpp
)

set (HEADERS
    ${RENDERER_PATH}/Renderer.h
    ${RENDERER_PATH}/IRendererModule.h
    ${RENDERER_PATH}/Window.h
    ${RENDERER_PATH}/GL/GLAPI.h
    ${RENDERER_PATH}/GL/GLPlatform.h
    ${RENDERER_PATH}/GL/GLRenderer.h
    ${RENDERER_PATH}/GL/GLRendererModule.h
    ${RENDERER_PATH}/GL/GLUtils.h
    ${RENDERER_PATH}/GL/GLWindow.h
    ${RENDERER_PATH}/GL/IGLContext.h
    ${RENDERER_PATH}/GL/HAL/GLApi.h
    ${RENDERER_PATH}/GL/HAL/GLContext.h
)

include_directories (
    ${SRCS_PATH}
    ${VENDORS_PATH}/OpenGL
)

if (WIN32)
    set (SOURCES ${SOURCES}
        ${RENDERER_PATH}/GL/windows/GLContextWGL.cpp
        ${RENDERER_PATH}/GL/windows/GLPlatform.cpp
    )

    set (HEADERS ${HEADERS}
        ${RENDERER_PATH}/GL/windows/GLContextWGL.h
        ${RENDERER_PATH}/GL/windows/WGLApi.h
    )

    set (ADDITIONAL_LIBRARIES gdi32)
endif (WIN32)

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

add_definitions (-DRENDERER_GL_API_EXPORT -DMODULE_NAME="Renderer.OpenGL")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries (${PROJECT_NAME} CodeHero.Core ${ADDITIONAL_LIBRARIES})
add_dependencies (${PROJECT_NAME} CodeHero.Platform)
