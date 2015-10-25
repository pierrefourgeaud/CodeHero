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
set (SRCS_PATH ${PROJECT_SOURCE_DIR}/src)
# set (DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/Dependencies)

set(SOURCES
  ${SRCS_PATH}/main.cpp
)

set(INCLUDES
)

include_directories(
  ${SRCS_PATH}
)

add_executable(CodeHero ${INCLUDES} ${SOURCES})