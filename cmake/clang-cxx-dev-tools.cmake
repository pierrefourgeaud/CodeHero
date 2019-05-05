# Courtesy of http://www.labri.fr/perso/fleury/posts/programming/using-clang-tidy-and-clang-format.html
# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     ${SRCS_PATH}/*.[chi]pp
     ${SRCS_PATH}/*.[chi]xx
     ${SRCS_PATH}/*.cc
     ${SRCS_PATH}/*.hh
     ${SRCS_PATH}/*.h
     ${SRCS_PATH}/*.ii
     ${SRCS_PATH}/*.[CHI]

     ${SPECS_PATH}/*.[chi]pp
     ${SPECS_PATH}/*.[chi]xx
     ${SPECS_PATH}/*.cc
     ${SPECS_PATH}/*.hh
     ${SPECS_PATH}/*.h
     ${SPECS_PATH}/*.ii
     ${SPECS_PATH}/*.[CHI]
     )
# set (ALL_CXX_SOURCE_FILES ${SOURCES} ${HEADERS})

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND clang-format
    -i
    -style=file
    ${ALL_CXX_SOURCE_FILES}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND /usr/bin/clang-tidy
    ${ALL_CXX_SOURCE_FILES}
    -config=''
    --
    -std=c++11
    ${INCLUDE_DIRECTORIES}
    )
endif()