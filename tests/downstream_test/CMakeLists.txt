cmake_minimum_required(VERSION 3.15)
project(docker_cpp_consumer_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find docker-cpp library
# This demonstrates how downstream projects would use the library
find_package(docker_cpp REQUIRED)

# Find other dependencies
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(consumer_example main.cpp)

target_link_libraries(consumer_example 
    PRIVATE 
        docker_cpp::docker_cpp
        spdlog::spdlog
        nlohmann_json::nlohmann_json
)

# Example: Link with pkg-config instead of CMake
# Uncomment to test pkg-config integration
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(DOCKER_CPP REQUIRED docker_cpp)
# target_link_directories(consumer_example PRIVATE ${DOCKER_CPP_LIBRARY_DIRS})
# target_include_directories(consumer_example PRIVATE ${DOCKER_CPP_INCLUDE_DIRS})
# target_link_libraries(consumer_example PRIVATE ${DOCKER_CPP_LIBRARIES})
