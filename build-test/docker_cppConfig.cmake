

include(CMakeFindDependencyMacro)

# Find required dependencies
find_dependency(Boost REQUIRED)
find_dependency(CURL REQUIRED)
find_dependency(spdlog REQUIRED)

# Include the targets file
include("${CMAKE_CURRENT_LIST_DIR}/docker_cppTargets.cmake")

# Create an alias for easy import
if(NOT TARGET docker_cpp::docker_cpp)
  add_library(docker_cpp::docker_cpp ALIAS docker_cpp_client)
endif()

message(STATUS "docker-cpp version 0.1.0 found")
