# Copyright 2026 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.14...4.2)

project(sendosio LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    # required for beman::execution
    set(CMAKE_CXX_STANDARD 23)

endif()

add_library(sendosio
    src/sendosio.cpp
)

add_library(sendosio::sendosio ALIAS sendosio)

target_include_directories(sendosio PUBLIC include)

target_link_libraries(sendosio
PUBLIC
    Boost::asio
    beman::execution_headers
)

target_compile_features(sendosio PUBLIC cxx_std_20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)

    include(CTest)

    include(FetchContent)

    # Boost

    message(STATUS "Fetching Boost")

    FetchContent_Declare(
      Boost
      URL https://github.com/boostorg/boost/releases/download/boost-1.90.0/boost-1.90.0-cmake.tar.xz
      URL_HASH SHA256=aca59f889f0f32028ad88ba6764582b63c916ce5f77b31289ad19421a96c555f
      DOWNLOAD_EXTRACT_TIMESTAMP ON
    )

    set(BOOST_INCLUDE_LIBRARIES asio)

    FetchContent_MakeAvailable(Boost)

    # beman.execution

    FetchContent_Declare(
        beman_execution
        GIT_REPOSITORY https://github.com/bemanproject/execution
        GIT_TAG 09d5a5c
        SYSTEM
        FIND_PACKAGE_ARGS
            0.2.0
            EXACT
            NAMES
            beman.execution
            COMPONENTS
            execution_headers
    )

    set(BEMAN_USE_MODULES OFF)

    FetchContent_MakeAvailable(beman_execution)

endif()

if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")

    add_subdirectory(test)

endif()
