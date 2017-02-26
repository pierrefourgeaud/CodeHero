cmake_minimum_required (VERSION 2.8)

project (CodeHero)

# ---------- C++ 11 flags ----------
if (${MSVC})
        set (CMAKE_CXX_FLAGS "/EHsc")
else (${MSVC})
        set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif (${MSVC})

# ---------- Build type flags ----------
if (BUILD_DEBUG)
    add_definitions (-DBUILD_DEBUG)
    set (CMAKE_BUILD_TYPE Debug)
    if (APPLE)
        set(CMAKE_MACOSX_RPATH 1)
    endif ()
else ()
    set (CMAKE_BUILD_TYPE RelWithDebInfo)
    if (APPLE)
        set(CMAKE_MACOSX_RPATH 0)
    endif ()
endif ()

# ---------- Setup the executable output directory ----------
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin CACHE PATH "Single directory for all executables.")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib CACHE PATH "Single directory for all executables.")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib CACHE PATH "Single directory for all executables.")

# ---------- Useful variables ----------
set (SRCS_PATH ${PROJECT_SOURCE_DIR}/codehero)
set (VENDORS_PATH ${PROJECT_SOURCE_DIR}/vendor)
# set (DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/Dependencies)

# ---------- Options ----------
option (_CODEHERO_DRIVER_PNG "Enable PNG driver" ON)
option (_CODEHERO_DRIVER_FREETYPE "Enable FreeType driver" ON)
option (_CODEHERO_DRIVER_ASSIMP "Enable Assimp driver" ON)

##### Options overview #####
message ("*** Configure options:")
message ("DRIVER_PNG: " ${_CODEHERO_DRIVER_PNG})
message ("VENDORS_PATH: " ${VENDORS_PATH})
message ("")
#####

# ---------- GLFW ----------
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (${VENDORS_PATH}/glfw)

# ---------- Sources ----------
file (GLOB VENDORS_SOURCES ${VENDORS_PATH}/glad/src/glad.c)

source_group ("Vendors" FILES ${VENDORS_SOURCES})

set (SOURCES
     ${VENDORS_SOURCES}
     ${SRCS_PATH}/main.cpp
     ${SRCS_PATH}/main/main.cpp
     ${SRCS_PATH}/core/enginecontext.cpp
     ${SRCS_PATH}/core/fileaccess.cpp
     ${SRCS_PATH}/core/filesystem.cpp
     ${SRCS_PATH}/core/image.cpp
     ${SRCS_PATH}/core/math/vector2.cpp
     ${SRCS_PATH}/core/math/vector3.cpp
     ${SRCS_PATH}/core/math/vector4.cpp
     ${SRCS_PATH}/core/math/matrix4.cpp
     # UI
     ${SRCS_PATH}/ui/font.cpp
     ${SRCS_PATH}/ui/fontface.cpp
     ${SRCS_PATH}/ui/fontface_freetype.cpp
     ${SRCS_PATH}/ui/text.cpp
     ${SRCS_PATH}/ui/ui.cpp
     ${SRCS_PATH}/ui/uibatch.cpp
     ${SRCS_PATH}/ui/uielement.cpp
     # Graphics
     ${SRCS_PATH}/graphics/camera.cpp
     ${SRCS_PATH}/graphics/component.cpp
     ${SRCS_PATH}/graphics/light.cpp
     ${SRCS_PATH}/graphics/node.cpp
     ${SRCS_PATH}/graphics/rendersystem.cpp
     ${SRCS_PATH}/graphics/renderwindow.cpp
     ${SRCS_PATH}/graphics/scene.cpp
     ${SRCS_PATH}/core/texturemanager.cpp
     ${SRCS_PATH}/core/texture.cpp
     ${SRCS_PATH}/graphics/viewport.cpp
     ${SRCS_PATH}/rendersystems/GL/shaderGL.cpp
     ${SRCS_PATH}/rendersystems/GL/rendersystemGL.cpp
     ${SRCS_PATH}/rendersystems/GL/renderwindowGL.cpp
     ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.cpp
     ${SRCS_PATH}/rendersystems/GL/textureGL.cpp
     ${SRCS_PATH}/rendersystems/GL/vertexattribbinding.cpp
     ${SRCS_PATH}/rendersystems/GL/vertexbufferGL.cpp
)

set (HEADERS
     ${SRCS_PATH}/main/main.h
     ${SRCS_PATH}/core/assert.h
     ${SRCS_PATH}/core/enginecontext.h
     ${SRCS_PATH}/core/errors.h
     ${SRCS_PATH}/core/object.h
     ${SRCS_PATH}/core/system.h
     ${SRCS_PATH}/core/typedefs.h
     ${SRCS_PATH}/core/utils.h
     ${SRCS_PATH}/core/shader.h
     ${SRCS_PATH}/core/fileaccess.h
     ${SRCS_PATH}/core/filesystem.h
     ${SRCS_PATH}/core/gpuobject.h
     ${SRCS_PATH}/core/image.h
     ${SRCS_PATH}/core/math/vector2.h
     ${SRCS_PATH}/core/math/vector3.h
     ${SRCS_PATH}/core/math/matrix4.h
     ${SRCS_PATH}/core/math/utils.h
     ${SRCS_PATH}/core/resourcecodec.h
     ${SRCS_PATH}/core/resourceloader.h
     # UI
     ${SRCS_PATH}/ui/font.h
     ${SRCS_PATH}/ui/fontface.h
     ${SRCS_PATH}/ui/fontface_freetype.h
     ${SRCS_PATH}/ui/text.h
     ${SRCS_PATH}/ui/ui.h
     ${SRCS_PATH}/ui/uibatch.h
     ${SRCS_PATH}/ui/uielement.h
     # Graphics
     ${SRCS_PATH}/graphics/camera.h
     ${SRCS_PATH}/graphics/component.h
     ${SRCS_PATH}/graphics/light.h
     ${SRCS_PATH}/graphics/node.h
     ${SRCS_PATH}/graphics/rendersystem.h
     ${SRCS_PATH}/graphics/renderwindow.h
     ${SRCS_PATH}/graphics/scene.h
     ${SRCS_PATH}/core/texturemanager.h
     ${SRCS_PATH}/core/texture.h
     ${SRCS_PATH}/graphics/vertexbuffer.h
     ${SRCS_PATH}/graphics/viewport.h
     ${SRCS_PATH}/rendersystems/GL/rendersystemGL.h
     ${SRCS_PATH}/rendersystems/GL/shaderGL.h
     ${SRCS_PATH}/rendersystems/GL/renderwindowGL.h
     ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.h
     ${SRCS_PATH}/rendersystems/GL/textureGL.h
     ${SRCS_PATH}/rendersystems/GL/vertexattribbinding.h
     ${SRCS_PATH}/rendersystems/GL/vertexbufferGL.h
     # Logger
     ${VENDORS_PATH}/simplelogger/includes/bufferlogger.h
     ${VENDORS_PATH}/simplelogger/includes/consolelogger.h
     ${VENDORS_PATH}/simplelogger/includes/filelogger.h
     ${VENDORS_PATH}/simplelogger/includes/iloglistener.h
     ${VENDORS_PATH}/simplelogger/includes/logger.h
)

include_directories (
  ${SRCS_PATH}
  ${VENDORS_PATH}/glad/include/
  ${VENDORS_PATH}/glfw/include/
  ${VENDORS_PATH}/simplelogger/includes
)

# ---------- Drivers -----------
# TODO(pierre) export that to function
if (${_CODEHERO_DRIVER_PNG})
    add_subdirectory (${VENDORS_PATH}/libpng)
    include_directories (${VENDORS_PATH}/libpng/)
    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/png/imagecodec_png.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/png/imagecodec_png.h
    )

    add_definitions (-DDRIVER_PNG)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} png16)
endif()

if (${_CODEHERO_DRIVER_FREETYPE})
    include_directories(${VENDORS_PATH}/freetype/include)
    add_subdirectory (${VENDORS_PATH}/freetype)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} freetype)
endif ()

if (${_CODEHERO_DRIVER_ASSIMP})
    add_subdirectory (${VENDORS_PATH}/assimp)
    set (SOURCES ${SOURCES}
         ${SRCS_PATH}/drivers/assimp/modelcodec_assimp.cpp
    )

    set (HEADERS ${HEADERS}
         ${SRCS_PATH}/drivers/assimp/modelcodec_assimp.h
    )

    add_definitions (-DDRIVER_ASSIMP)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} assimp)
endif ()

# ---------- Flags ----------
set (COMMON_RELEASE_FLAGS "-fPIC -g -O3 -fstack-protector -fvisibility=hidden -W -Wall -Wno-missing-braces -Wno-unused-function -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated -Wformat-security -Werror")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_RELEASE_FLAGS}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${COMMON_RELEASE_FLAGS}")

# ---------- Executables -----------

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_executable (CodeHero ${INCLUDES} ${SOURCES} ${HEADERS})

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${ADDITIONAL_LIBRARIES})
