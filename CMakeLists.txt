
cmake_minimum_required (VERSION 3.7)

project (fsio C)

# include shared utilities
if(NOT EXISTS "target/cmake-modules/src/utils.cmake")
  execute_process(COMMAND git clone https://github.com/sagiegurari/cmake-modules.git)
endif()
include("target/cmake-modules/src/utils.cmake")

set(CMAKE_BUILD_TYPE Release)
if(NOT WIN32)
  set(X_CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wcast-align -Wunused -Wshadow -Wpedantic")
endif()

set(X_CMAKE_PROJECT_ROOT_DIR ${CMAKE_BINARY_DIR}/..)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

macro(add_external_lib)
  utils_add_external_github_lib(
    REPO_USERNAME sagiegurari
    REPO_NAME c_${ARGV0}
    TAG_NAME ${ARGV1}
    LIBRARY_NAME ${ARGV0}
    LIBRARY_PARENT_DIRECTORY target
  )
endmacro(add_external_lib)
add_external_lib("string_buffer" "v0.1.2")

include_directories(include "${STRING_BUFFER_INCLUDE}")

# define all sources
file(GLOB SOURCES "src/*.c")
file(GLOB HEADER_SOURCES "include/*.h")
file(GLOB TEST_SOURCES "tests/*")
file(GLOB COMMON_TEST_SOURCES "tests/test.*")
file(GLOB EXAMPLE_SOURCES "example/*.c")

# format code
if(DEFINED ENV{X_CMAKE_UNCRUSTIFY_ENABLED})
  add_custom_target(uncrustify ALL
    uncrustify
    -c ${X_CMAKE_PROJECT_ROOT_DIR}/uncrustify.cfg
    --no-backup ${SOURCES} ${HEADER_SOURCES} ${TEST_SOURCES} ${EXAMPLE_SOURCES})
endif()

# create static library
add_library(fsio STATIC ${SOURCES} ${STRING_BUFFER_SOURCES})
if(NOT WIN32)
  set_target_properties(fsio PROPERTIES COMPILE_FLAGS "${X_CMAKE_C_FLAGS} -Wconversion")
endif()

# example
add_executable(example examples/example.c)
target_link_libraries(example fsio)
set_target_properties(example PROPERTIES COMPILE_FLAGS "${X_CMAKE_C_FLAGS}")

# tests
enable_testing()

utils_setup_c_test(
  NAME
    write_text_file_null_file
    write_text_file_null_text
    write_text_file_dir_not_exists
    write_text_file_empty
    write_text_file_content
    write_text_file_long_content
    write_text_file_overwrite
    write_text_file_stress
    append_text_file_content
    read_text_file_not_found
    dir_exists_null
    dir_exists_file
    dir_exists_dir
    dir_exists_not_found
    mkdir_null
    mkdirs_null
  ADDITIONAL_SOURCES "${COMMON_TEST_SOURCES}"
  COMPILATION_FLAGS "${X_CMAKE_C_FLAGS}"
  BINARY_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

