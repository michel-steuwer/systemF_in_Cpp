cmake_minimum_required(VERSION 3.11)
project(test-systemF)

include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.2.2
)

FetchContent_GetProperties(catch2)

if(NOT catch2_POPULATED)
  FetchContent_Populate(catch2)
  add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
endif()

enable_testing()

add_executable(test-first first.cpp)
target_link_libraries(test-first systemF Catch2::Catch)
add_test(NAME first COMMAND test-first)