cmake_minimum_required(VERSION 3.11)
project(systemF VERSION 0.1)

add_compile_options(-W -Wall -Werror)

add_library(systemF SHARED)

target_sources(systemF
    PRIVATE
        src/expr.cpp
        src/show.cpp
        src/type.cpp
        src/typecheck.cpp
        src/util.cpp
    )
target_include_directories(systemF
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
    )
target_compile_features(systemF PUBLIC cxx_std_20)

add_subdirectory(test)