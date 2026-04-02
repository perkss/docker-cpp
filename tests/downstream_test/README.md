# Docker-CPP Consumer Example

This directory contains an example of how downstream projects would integrate and use the `docker-cpp` library after installation.

## Purpose

This example demonstrates:
- How to use `find_package()` to locate the installed `docker-cpp` library
- How to link against the library using CMake targets
- How to use the Docker client API
- Error handling and logging patterns

## Building the Example

### Prerequisites

You must first build and install docker-cpp:

```bash
# From the docker-cpp root directory
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -G Ninja -S . -B build
cmake --build build
sudo cmake --install build --prefix /usr
```

### Build the Example

```bash
# Build locally
cmake -S . -B build
cmake --build build

# Or build with explicit docker-cpp path if not installed system-wide
cmake -DCMAKE_PREFIX_PATH=/path/to/install/lib/cmake -S . -B build
cmake --build build
```

### Run the Example

```bash
# Make sure Docker daemon is running
./build/consumer_example
```

Expected output:
```
=== docker-cpp Consumer Example ===
Library Version: 0.1.0
Creating Docker client...

[Test 1] Pinging Docker daemon...
✓ Docker daemon is responding

[Test 2] Getting Docker version...
✓ Docker API Version: 1.43
  OS: linux

[Test 3] Getting Docker info...
✓ Docker Info retrieved
  Containers: 5
  Images: 12
  Memory: 31862 MB

=== All tests passed successfully! ===
docker-cpp library integration complete.
```

## Integration Methods

### Method 1: CMake find_package() (Recommended)

```cmake
find_package(docker_cpp REQUIRED)

add_executable(myapp myapp.cpp)
target_link_libraries(myapp PRIVATE docker_cpp::docker_cpp)
```

### Method 2: pkg-config

```bash
g++ -std=c++20 main.cpp \
    $(pkg-config --cflags --libs docker_cpp) \
    -o consumer_example
```

Or in CMake:
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(DOCKER_CPP REQUIRED docker_cpp)

add_executable(myapp myapp.cpp)
target_include_directories(myapp PRIVATE ${DOCKER_CPP_INCLUDE_DIRS})
target_link_directories(myapp PRIVATE ${DOCKER_CPP_LIBRARY_DIRS})
target_link_libraries(myapp PRIVATE ${DOCKER_CPP_LIBRARIES})
```

## Common Usage Patterns

### 1. Connect and Test Connection

```cpp
dockercpp::DockerClient client;
dockercpp::PingCmd ping_cmd;
ping_cmd.exec(client);  // Throws if Docker unreachable
```

### 2. Query Docker Information

```cpp
dockercpp::VersionCmd version_cmd;
auto version = version_cmd.exec(client);
std::cout << "API Version: " << version.apiVersion << std::endl;

dockercpp::InfoCmd info_cmd;
auto info = info_cmd.exec(client);
std::cout << "Docker Containers: " << info.containers << std::endl;
```

### 3. Work with Images

```cpp
dockercpp::PullImageCmd pull_cmd("ubuntu:latest");
pull_cmd.exec(client);  // Throws if fails

dockercpp::InspectImageCmd inspect_cmd("ubuntu:latest");
auto image = inspect_cmd.exec(client);
std::cout << "Image ID: " << image.id << std::endl;
```

### 4. Manage Containers

```cpp
// Create
dockercpp::CreateContainerCmd create_cmd("ubuntu:latest");
auto response = create_cmd.exec(client);
std::string container_id = response.id;

// Start
dockercpp::StartContainerCmd start_cmd(container_id);
start_cmd.exec(client);

// Inspect
dockercpp::InspectContainerCmd inspect_cmd(container_id);
auto container = inspect_cmd.exec(client);
std::cout << "Running: " << container.state.running << std::endl;

// Stop
dockercpp::StopContainerCmd stop_cmd(container_id);
stop_cmd.exec(client);

// Remove
dockercpp::RemoveContainerCmd remove_cmd(container_id);
remove_cmd.exec(client);
```

## Error Handling

All docker-cpp API calls may throw `dockercpp::DockerException`:

```cpp
try {
    dockercpp::PullImageCmd pull_cmd("nonexistent-image:latest");
    pull_cmd.exec(client);
} catch (const dockercpp::DockerException& e) {
    std::cerr << "Docker error: " << e.what() << std::endl;
}
```

## Next Steps

- For full API documentation, see the [docker-cpp README](../../README.md)
- Check header files in `/usr/include/docker_cpp/` for available commands
- Review [PACKAGING.md](../../docs/PACKAGING.md) for distribution details
- See the main test suite in [tests/readme_examples_test.cc](../readme_examples_test.cc)
