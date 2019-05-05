cmake_minimum_required (VERSION 2.8)

project (Specs)
set (TARGET_NAME CodeHero${PROJECT_NAME})
message (${TARGET_NAME})

FILE(GLOB SPEC_SOURCES
    ${SPECS_PATH}/*.cpp
    ${SPECS_PATH}/**/*.cpp
    ${SPECS_PATH}/**/**/*.cpp
    ${SPECS_PATH}/**/**/**/*.cpp

    ${SPECS_PATH}/*.h
    ${SPECS_PATH}/**/*.h
    ${SPECS_PATH}/**/**/*.h
)

include_directories (
    ${SPECS_PATH}
    ${VENDORS_PATH}/bandit
)

# ---------- Coverage -----------
add_executable (${TARGET_NAME} ${SPEC_SOURCES} $<TARGET_OBJECTS:main_objs>)
target_link_libraries (${TARGET_NAME} glfw ${GLFW_LIBRARIES} ${ADDITIONAL_LIBRARIES})