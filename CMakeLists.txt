cmake_minimum_required(VERSION 4.2.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CTEST_OUTPUT_ON_FAILURE ON)
set(CMAKE_CXX_STANDARD 20)

# Version information
set(DOCKER_CPP_VERSION_MAJOR 0)
set(DOCKER_CPP_VERSION_MINOR 1)
set(DOCKER_CPP_VERSION_PATCH 0)
set(DOCKER_CPP_VERSION_STRING "${DOCKER_CPP_VERSION_MAJOR}.${DOCKER_CPP_VERSION_MINOR}.${DOCKER_CPP_VERSION_PATCH}")

# Build configuration options
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_TESTS "Build test suite" ON)

# Allow Release/Debug to be specified from command line, default to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Debug/Release)" FORCE)
endif()

#set(CMAKE_CXX_CPPCHECK "cppcheck")
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
#set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

project(docker_cpp
  VERSION ${DOCKER_CPP_VERSION_STRING}
  DESCRIPTION "A container client for c++"
  LANGUAGES CXX
  HOMEPAGE_URL "https://github.com/docker-cpp/docker-cpp")


find_package(Boost REQUIRED)
find_package(CURL REQUIRED)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
  endif()


enable_testing()

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Export targets for downstream projects
install(
  TARGETS docker_cpp_client
  EXPORT docker_cppTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
  EXPORT docker_cppTargets
  FILE docker_cppTargets.cmake
  NAMESPACE docker_cpp::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/docker_cpp
)

# Generate and install pkg-config file
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/docker_cpp.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/docker_cpp.pc"
  @ONLY
)
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/docker_cpp.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

# Generate CMake config files for downstream projects
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/docker_cppConfigVersion.cmake"
  VERSION ${DOCKER_CPP_VERSION_STRING}
  COMPATIBILITY SameMajorVersion
)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/docker_cppConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/docker_cppConfig.cmake"
  @ONLY
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/docker_cppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/docker_cppConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/docker_cpp"
)
