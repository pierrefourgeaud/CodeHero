cmake_minimum_required (VERSION 3.9)

project (CodeHero)

# ---------- C++ 11 flags ----------
if (${MSVC})
    set (CMAKE_CXX_FLAGS "/EHs")
    add_definitions (-D_CRT_SECURE_NO_WARNINGS)
    set (CODEHERO_CXX_FLAGS "/W4 /WX /wd4244 /wd4611")
elseif (APPLE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
else ()
    set (CMAKE_CXX_FLAGS "-std=c++11")
endif (${MSVC})

# ---------- Setup the executable output directory ----------
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin CACHE PATH "Single directory for all executables.")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib CACHE PATH "Single directory for all executables.")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/lib CACHE PATH "Single directory for all executables.")

# ---------- Useful variables ----------
set (SRCS_PATH ${PROJECT_SOURCE_DIR}/src)
set (VENDORS_PATH ${PROJECT_SOURCE_DIR}/vendor)
set (SPECS_PATH ${PROJECT_SOURCE_DIR}/specs)
# set (DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/Dependencies)

# Just get the size of the sources path at compile time
string(LENGTH "${SRCS_PATH}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

# ---------- Options ----------

##### Options overview #####
message ("*** Configure options:")
message ("VENDORS_PATH: " ${VENDORS_PATH})
message ("")
#####

set (SOURCES
     ${SRCS_PATH}/codehero/CodeHero.cpp
)

set (HEADERS
     ${SRCS_PATH}/codehero/CodeHero.h
)

include_directories (
  ${SRCS_PATH}
  ${VENDORS_PATH}/simplelogger/includes
)

# -

# ---------- Flags ----------
set (COMMON_RELEASE_FLAGS "-g -O3 -fstack-protector -fvisibility=hidden -W -Wall -Wpointer-arith -Wformat -Wreturn-type -Wsign-compare -Wmultichar -Wformat-nonliteral -Winit-self -Wuninitialized -Wno-deprecated -Wformat-security -Werror")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_RELEASE_FLAGS}")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${COMMON_RELEASE_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CODEHERO_CXX_FLAGS}")

# ---------- Executables -----------
add_library (main_objs OBJECT ${INCLUDES} ${SOURCES} ${HEADERS})

add_definitions (-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_executable (${PROJECT_NAME} ${SRCS_PATH}/main.cpp $<TARGET_OBJECTS:main_objs>)

target_link_libraries (${PROJECT_NAME} ${ADDITIONAL_LIBRARIES})

# Must be included after the sources and tests
include(cmake/clang-cxx-dev-tools.cmake)