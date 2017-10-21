cmake_minimum_required (VERSION 3.9)

project (CodeHero)

# ---------- C++ 11 flags ----------
if (${MSVC})
    set (CMAKE_CXX_FLAGS "/EHs")
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CODEHERO_CXX_FLAGS "/W4 /WX /wd4244 /wd4611")
elseif (APPLE)
    set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
else ()
    set (CMAKE_CXX_FLAGS "-std=c++11")
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
option (_CODEHERO_DRIVER_JPG "Enable JPG driver" ON)
option (_CODEHERO_DRIVER_DDS "Enable DDS driver" ON)
option (_CODEHERO_DRIVER_TGA "Enable TGA driver" ON)
option (_CODEHERO_DRIVER_FREETYPE "Enable FreeType driver" ON)
option (_CODEHERO_DRIVER_ASSIMP "Enable Assimp driver" ON)
option (_CODEHERO_DRIVER_PUGIXML "Enable PugiXML driver" ON)
option (_CODEHERO_BUILD_TESTS "Build the unit tests" OFF)

##### Options overview #####
message ("*** Configure options:")
message ("DRIVER_PNG: " ${_CODEHERO_DRIVER_PNG})
message ("DRIVER_JPG: " ${_CODEHERO_DRIVER_JPG})
message ("DRIVER_DDS: " ${_CODEHERO_DRIVER_DDS})
message ("DRIVER_TGA: " ${_CODEHERO_DRIVER_TGA})
message ("DRIVER_ASSIMP: " ${_CODEHERO_DRIVER_ASSIMP})
message ("DRIVER_PUGIXML: " ${_CODEHERO_DRIVER_PUGIXML})
message ("BUILD_TESTS: " ${_CODEHERO_BUILD_TESTS})
message ("DRIVER_FREETYPE: " ${_CODEHERO_DRIVER_FREETYPE})
message ("VENDORS_PATH: " ${VENDORS_PATH})
message ("")
#####

# ---------- GLFW ----------
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (${VENDORS_PATH}/glfw)

# Should this be optional ?
# For now we want other libs to use our zlib
# Used by libpng and assimp
set (ZLIB_FOUND 1)
set (ZLIB_LIBRARY zlibstatic)
set (ZLIB_LIBRARIES zlibstatic)
set (ZLIB_INCLUDE_DIR ${VENDORS_PATH}/zlib)
add_subdirectory (${VENDORS_PATH}/zlib)
include_directories (${VENDORS_PATH}/zlib ${CMAKE_CURRENT_BINARY_DIR}/vendor/zlib)
set (SKIP_INSTALL_ALL ON)

# ---------- Sources ----------
file (GLOB VENDORS_SOURCES ${VENDORS_PATH}/glad/src/glad.c)

source_group ("Vendors" FILES ${VENDORS_SOURCES})

set (SOURCES
     ${VENDORS_SOURCES}
     ${SRCS_PATH}/main/main.cpp
     ${SRCS_PATH}/core/enginecontext.cpp
     ${SRCS_PATH}/core/fileaccess.cpp
     ${SRCS_PATH}/core/filesystem.cpp
     ${SRCS_PATH}/core/image.cpp
     ${SRCS_PATH}/core/object.cpp
     ${SRCS_PATH}/core/time.cpp
     ${SRCS_PATH}/core/math/vector2.cpp
     ${SRCS_PATH}/core/math/vector3.cpp
     ${SRCS_PATH}/core/math/vector4.cpp
     ${SRCS_PATH}/core/math/matrix3.cpp
     ${SRCS_PATH}/core/math/matrix4.cpp
     ${SRCS_PATH}/core/math/quaternion.cpp
     ${SRCS_PATH}/core/serializable.cpp
     ${SRCS_PATH}/core/utils.cpp
     ${SRCS_PATH}/core/variant.cpp
     ${SRCS_PATH}/core/type_traits/objectdefinition.cpp
     # UI
     ${SRCS_PATH}/ui/font.cpp
     ${SRCS_PATH}/ui/fontface.cpp
     ${SRCS_PATH}/ui/fontface_freetype.cpp
     ${SRCS_PATH}/ui/text.cpp
     ${SRCS_PATH}/ui/ui.cpp
     ${SRCS_PATH}/ui/uibatch.cpp
     ${SRCS_PATH}/ui/uielement.cpp
     # Graphics
     ${SRCS_PATH}/graphics/bone.cpp
     ${SRCS_PATH}/graphics/batch.cpp
     ${SRCS_PATH}/graphics/camera.cpp
     ${SRCS_PATH}/graphics/cube.cpp
     ${SRCS_PATH}/graphics/drawable.cpp
     ${SRCS_PATH}/graphics/indexbuffer.cpp
     ${SRCS_PATH}/graphics/light.cpp
     ${SRCS_PATH}/graphics/material.cpp
     ${SRCS_PATH}/graphics/mesh.cpp
     ${SRCS_PATH}/graphics/model.cpp
     ${SRCS_PATH}/graphics/node.cpp
     ${SRCS_PATH}/graphics/plane.cpp
     ${SRCS_PATH}/graphics/rendersystem.cpp
     ${SRCS_PATH}/graphics/renderwindow.cpp
     ${SRCS_PATH}/graphics/scene.cpp
     ${SRCS_PATH}/graphics/shader.cpp
     ${SRCS_PATH}/graphics/shaderprogram.cpp
     ${SRCS_PATH}/graphics/skybox.cpp
     ${SRCS_PATH}/core/texturemanager.cpp
     ${SRCS_PATH}/core/texture.cpp
     ${SRCS_PATH}/graphics/viewport.cpp
     ${SRCS_PATH}/rendersystems/GL/shaderGL.cpp
     ${SRCS_PATH}/rendersystems/GL/shaderprogramGL.cpp
     ${SRCS_PATH}/rendersystems/GL/rendersystemGL.cpp
     ${SRCS_PATH}/rendersystems/GL/renderwindowGL.cpp
     ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.cpp
     ${SRCS_PATH}/rendersystems/GL/textureGL.cpp
     ${SRCS_PATH}/rendersystems/GL/vertexattribbinding.cpp
     ${SRCS_PATH}/rendersystems/GL/vertexbufferGL.cpp
     ${SRCS_PATH}/rendersystems/GL/indexbufferGL.cpp
     # Inputs
     ${SRCS_PATH}/input/input.cpp
)

set (HEADERS
     ${SRCS_PATH}/main/main.h
     ${SRCS_PATH}/core/assert.h
     ${SRCS_PATH}/core/enginecontext.h
     ${SRCS_PATH}/core/errors.h
     ${SRCS_PATH}/core/object.h
     ${SRCS_PATH}/core/system.h
     ${SRCS_PATH}/core/time.h
     ${SRCS_PATH}/core/typedefs.h
     ${SRCS_PATH}/core/utils.h
     ${SRCS_PATH}/core/fileaccess.h
     ${SRCS_PATH}/core/filesystem.h
     ${SRCS_PATH}/core/gpuobject.h
     ${SRCS_PATH}/core/image.h
     ${SRCS_PATH}/core/scopecleaner.h
     ${SRCS_PATH}/core/math/vector2.h
     ${SRCS_PATH}/core/math/vector3.h
     ${SRCS_PATH}/core/math/vector4.h
     ${SRCS_PATH}/core/math/matrix3.h
     ${SRCS_PATH}/core/math/matrix4.h
     ${SRCS_PATH}/core/math/quaternion.h
     ${SRCS_PATH}/core/math/utils.h
     ${SRCS_PATH}/core/resourcecodec.h
     ${SRCS_PATH}/core/resourceloader.h
     ${SRCS_PATH}/core/serializable.h
     ${SRCS_PATH}/core/variant.h
     ${SRCS_PATH}/core/type_traits/attributeaccessor.h
     ${SRCS_PATH}/core/type_traits/attributeaccessor_impl.h
     ${SRCS_PATH}/core/type_traits/attributeaccessorcast_impl.h
     ${SRCS_PATH}/core/type_traits/attributeaccessorcustom_impl.h
     ${SRCS_PATH}/core/type_traits/attributeaccessorenum_impl.h
     ${SRCS_PATH}/core/type_traits/attributeinfo.h
     ${SRCS_PATH}/core/type_traits/objectdefinition.h
     # UI
     ${SRCS_PATH}/ui/font.h
     ${SRCS_PATH}/ui/fontface.h
     ${SRCS_PATH}/ui/fontface_freetype.h
     ${SRCS_PATH}/ui/text.h
     ${SRCS_PATH}/ui/ui.h
     ${SRCS_PATH}/ui/uibatch.h
     ${SRCS_PATH}/ui/uielement.h
     # Graphics
     ${SRCS_PATH}/graphics/batch.h
     ${SRCS_PATH}/graphics/bone.h
     ${SRCS_PATH}/graphics/camera.h
     ${SRCS_PATH}/graphics/cube.h
     ${SRCS_PATH}/graphics/drawable.h
     ${SRCS_PATH}/graphics/indexbuffer.h
     ${SRCS_PATH}/graphics/light.h
     ${SRCS_PATH}/graphics/mesh.h
     ${SRCS_PATH}/graphics/material.h
     ${SRCS_PATH}/graphics/model.h
     ${SRCS_PATH}/graphics/node.h
     ${SRCS_PATH}/graphics/plane.h
     ${SRCS_PATH}/graphics/rendersystem.h
     ${SRCS_PATH}/graphics/renderwindow.h
     ${SRCS_PATH}/graphics/scene.h
     ${SRCS_PATH}/graphics/shader.h
     ${SRCS_PATH}/graphics/shaderprogram.h
     ${SRCS_PATH}/graphics/skybox.h
     ${SRCS_PATH}/core/texturemanager.h
     ${SRCS_PATH}/core/texture.h
     ${SRCS_PATH}/graphics/vertexbuffer.h
     ${SRCS_PATH}/graphics/viewport.h
     ${SRCS_PATH}/rendersystems/GL/rendersystemGL.h
     ${SRCS_PATH}/rendersystems/GL/shaderGL.h
     ${SRCS_PATH}/rendersystems/GL/shaderprogramGL.h
     ${SRCS_PATH}/rendersystems/GL/renderwindowGL.h
     ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.h
     ${SRCS_PATH}/rendersystems/GL/textureGL.h
     ${SRCS_PATH}/rendersystems/GL/vertexattribbinding.h
     ${SRCS_PATH}/rendersystems/GL/vertexbufferGL.h
     ${SRCS_PATH}/rendersystems/GL/indexbufferGL.h
     # Inputs
     ${SRCS_PATH}/input/input.h
     ${SRCS_PATH}/input/inputevents.h
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
    set (PNG_TESTS OFF CACHE BOOL "" FORCE)
    set (PNG_SHARED OFF CACHE BOOL "" FORCE)
    set (PNG_STATIC ON CACHE BOOL "" FORCE)
    add_subdirectory (${VENDORS_PATH}/libpng)
    include_directories (${VENDORS_PATH}/libpng/)
    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/png/imagecodec_png.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/png/imagecodec_png.h
    )

    add_definitions (-DDRIVER_PNG)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} png16_static)
endif()

if (${_CODEHERO_DRIVER_JPG})
    include_directories (SYSTEM ${VENDORS_PATH}/jpeg-compressor/)
    set (SOURCES ${SOURCES}
        ${VENDORS_PATH}/jpeg-compressor/jpgd.cpp
        ${SRCS_PATH}/drivers/jpg/imagecodec_jpg.cpp
    )

    # Disable some warnings..
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set_source_files_properties(${VENDORS_PATH}/jpeg-compressor/jpgd.cpp PROPERTIES COMPILE_FLAGS "-Wno-shift-negative-value -Wno-unused-parameter")
    elseif (${MSVC})
        set_source_files_properties(${VENDORS_PATH}/jpeg-compressor/jpgd.cpp PROPERTIES COMPILE_FLAGS "/wd4458")
    endif ()

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/jpg/imagecodec_jpg.h
    )

    add_definitions (-DDRIVER_JPG)
endif()

if (${_CODEHERO_DRIVER_DDS})
    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/dds/imagecodec_dds.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/dds/imagecodec_dds.h
    )

    add_definitions (-DDRIVER_DDS)
endif()

if (${_CODEHERO_DRIVER_TGA})
    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/tga/imagecodec_tga.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/tga/imagecodec_tga.h
    )

    add_definitions (-DDRIVER_TGA)
endif()

if (${_CODEHERO_DRIVER_FREETYPE})
    include_directories(${VENDORS_PATH}/freetype/include)
    add_subdirectory (${VENDORS_PATH}/freetype)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} freetype)
endif ()

if (${_CODEHERO_DRIVER_ASSIMP})
    set (ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set (ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
    set (ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
    set (ASSIMP_NO_EXPORT OFF CACHE BOOL "" FORCE)
    set (ASSIMP_INSTALL_PDB OFF CACHE BOOL "" FORCE)

    add_subdirectory (${VENDORS_PATH}/assimp)
    include_directories (
        SYSTEM ${VENDORS_PATH}/assimp/include
        # This is a hack because the new Assimp build is somehow a bit stupid on that...
        SYSTEM ${CMAKE_BINARY_DIR}/vendor/assimp/include
    )

    set (SOURCES ${SOURCES}
         ${SRCS_PATH}/drivers/assimp/modelcodec_assimp.cpp
         ${SRCS_PATH}/drivers/assimp/iosystem.cpp
    )

    set (HEADERS ${HEADERS}
         ${SRCS_PATH}/drivers/assimp/modelcodec_assimp.h
         ${SRCS_PATH}/drivers/assimp/iosystem.h
    )

    add_definitions (-DDRIVER_ASSIMP)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} assimp)
endif ()

if (${_CODEHERO_DRIVER_PUGIXML})
    add_subdirectory (${VENDORS_PATH}/pugixml)
    include_directories (SYSTEM ${VENDORS_PATH}/pugixml/src)

    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/xml/serializablecodec_xml.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/xml/serializablecodec_xml.h
    )

    add_definitions (-DDRIVER_PUGIXML)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} pugixml)
endif ()

# Source groups
source_group (TREE ${PROJECT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})
# -

# ---------- Flags ----------
set (COMMON_RELEASE_FLAGS "-fPIC -g -O3 -fstack-protector -fvisibility=hidden -W -Wall -Wno-missing-braces -Wno-unused-function -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated -Wformat-security -Werror")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_RELEASE_FLAGS}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${COMMON_RELEASE_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CODEHERO_CXX_FLAGS}")

# ---------- Executables -----------
add_library (main_objs OBJECT ${INCLUDES} ${SOURCES} ${HEADERS})

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_executable (${PROJECT_NAME} ${SRCS_PATH}/main.cpp $<TARGET_OBJECTS:main_objs>)

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${ADDITIONAL_LIBRARIES})

if (_CODEHERO_BUILD_TESTS)
    add_subdirectory (${PROJECT_SOURCE_DIR}/specs)
endif ()
