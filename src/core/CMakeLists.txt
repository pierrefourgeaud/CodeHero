cmake_minimum_required (VERSION 3.9)

project (CodeHero.Core)

set (CORE_PATH ${SRCS_PATH}/core)

set (SOURCES
     ${CORE_PATH}/logger/Logger.cpp
     ${CORE_PATH}/platform/common/CommonSharedLibraryHandler.cpp
     ${CORE_PATH}/platform/windows/SharedLibraryHandler.cpp
     ${CORE_PATH}/Core.cpp
     ${CORE_PATH}/ModuleManager.cpp
)

set (HEADERS
    ${CORE_PATH}/HAL/Platform.h
    ${CORE_PATH}/HAL/SharedLibraryHandler.h
    ${CORE_PATH}/logger/ILogListener.h
    ${CORE_PATH}/logger/Logger.h
    ${CORE_PATH}/logger/WConsoleLogger.h
    ${CORE_PATH}/platform/common/CommonSharedLibraryHandler.h
    ${CORE_PATH}/platform/windows/SharedLibraryHandler.h
    ${CORE_PATH}/Core.h
    ${CORE_PATH}/CoreAPI.h
    ${CORE_PATH}/Macros.h
    ${CORE_PATH}/Module.h
    ${CORE_PATH}/ModuleManager.h
    ${CORE_PATH}/String.h
    ${CORE_PATH}/TypeDefs.h
)

include_directories (
    ${SRCS_PATH}
)
add_definitions(-DCORE_API_EXPORT  -DMODULE_NAME="Core")

# ---------- Executables -----------
add_library (${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES} ${HEADERS})

link_directories (
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
