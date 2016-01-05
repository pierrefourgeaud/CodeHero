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

##### Options overview #####
message ("*** Configure options:")
message ("VENDORS_PATH: " ${VENDORS_PATH})
message ("")
#####

# ---------- GLFW ----------
option (GLFW_BUILD_DOCS OFF)
option (GLFW_BUILD_EXAMPLES OFF)
option (GLFW_BUILD_TESTS OFF)
add_subdirectory (vendor/glfw)

# ---------- Sources ----------
file (GLOB VENDORS_SOURCES ${VENDORS_PATH}/glad/src/glad.c)

source_group ("Vendors" FILES ${VENDORS_SOURCES})

set (SOURCES
  ${VENDORS_SOURCES}
  ${SRCS_PATH}/main.cpp
  ${SRCS_PATH}/main/main.cpp
  ${SRCS_PATH}/core/shader.cpp
  ${SRCS_PATH}/core/logging/Logger.cpp
)

include_directories (
  ${SRCS_PATH}/core
  ${SRCS_PATH}/main
  ${VENDORS_PATH}/glad/include/
  ${VENDORS_PATH}/glfw/include/
  ${VENDORS_PATH}/stb/
)

# ---------- Executables -----------

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable (CodeHero ${INCLUDES} ${SOURCES})

target_link_libraries (${PROJECT_NAME} glfw ${GLFW_LIBRARIES})