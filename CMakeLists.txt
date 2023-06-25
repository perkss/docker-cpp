cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CTEST_OUTPUT_ON_FAILURE ON)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_CPPCHECK "cppcheck")
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
#set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


# Temporary whilst we develop
set(CMAKE_BUILD_TYPE Debug)

project(docker_cpp
  VERSION 0.1
  DESCRIPTION "A container client for c++"
  LANGUAGES CXX)


find_package(Boost REQUIRED)
find_package(CURL REQUIRED)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
  endif()


enable_testing()

add_subdirectory(src)

add_subdirectory(tests)
