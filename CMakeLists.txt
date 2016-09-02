cmake_minimum_required (VERSION 2.8)

project (CodeHero)

# ---------- C++ 11 flags ----------
if (${MSVC})
        set (CMAKE_CXX_FLAGS "/EHsc")
else (${MSVC})
        set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif (${MSVC})

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
  ${SRCS_PATH}/core/shader.cpp
  ${SRCS_PATH}/core/fileaccess.cpp
  ${SRCS_PATH}/core/image.cpp
  ${SRCS_PATH}/core/imagecodec.cpp
  ${SRCS_PATH}/core/imageloader.cpp
  # Graphics
  ${SRCS_PATH}/core/rendersystem.cpp
  ${SRCS_PATH}/core/renderwindow.cpp
  ${SRCS_PATH}/core/texturemanager.cpp
  ${SRCS_PATH}/core/texture.cpp
  ${SRCS_PATH}/rendersystems/GL/rendersystemGL.cpp
  ${SRCS_PATH}/rendersystems/GL/renderwindowGL.cpp
  ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.cpp
  ${SRCS_PATH}/rendersystems/GL/textureGL.cpp
)

set (HEADERS
    ${SRCS_PATH}/main/main.h
    ${SRCS_PATH}/core/errors.h
    ${SRCS_PATH}/core/typedefs.h
    ${SRCS_PATH}/core/utils.h
    ${SRCS_PATH}/core/shader.h
    ${SRCS_PATH}/core/fileaccess.h
    ${SRCS_PATH}/core/image.h
    ${SRCS_PATH}/core/imagecodec.h
    ${SRCS_PATH}/core/imageloader.h
    # Graphics
    ${SRCS_PATH}/core/rendersystem.h
    ${SRCS_PATH}/core/renderwindow.h
    ${SRCS_PATH}/core/texturemanager.h
    ${SRCS_PATH}/core/texture.h
    ${SRCS_PATH}/rendersystems/GL/rendersystemGL.h
    ${SRCS_PATH}/rendersystems/GL/renderwindowGL.h
    ${SRCS_PATH}/rendersystems/GL/texturemanagerGL.h
    ${SRCS_PATH}/rendersystems/GL/textureGL.h
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
  ${VENDORS_PATH}/stb/
  ${VENDORS_PATH}/libpng/
  ${VENDORS_PATH}/simplelogger/includes
)

# ---------- Drivers -----------
# TODO(pierre) export that to function
if (${_CODEHERO_DRIVER_PNG})
    add_subdirectory (${VENDORS_PATH}/libpng)
    set (SOURCES ${SOURCES}
        ${SRCS_PATH}/drivers/png/imagecodec_png.cpp
    )

    set (HEADERS ${HEADERS}
        ${SRCS_PATH}/drivers/png/imagecodec_png.h
    )

    add_definitions (-DDRIVER_PNG)
    set (ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} png16)
endif()

# ---------- Executables -----------

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_executable (CodeHero ${INCLUDES} ${SOURCES} ${HEADERS})

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${ADDITIONAL_LIBRARIES})
