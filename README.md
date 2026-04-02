# docker-cpp
Docker Client for C++.

## Introduction

The Docker Client for C++ is a client api for executing docker commands from C++.

## Contributions

Contributions are welcome please see the [Contributing.md](CONTRIBUTING.md).

## Dependencies

* spdlog
* curl
* boost

## Build

```
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja -S . -B build 
cmake --build build
cmake --build build -t test
```

## Ensure Docker Destop

Allow the default Docker socket to be used (requires password). Is enabled if using docker desktop. The `/var/run/docker.sock` is required. 

## Getting Started

The tests folder contains many examples of using the docker client for c++ this is a great place to look.

### Basic Connection Test

Start with a simple ping to verify Docker is accessible:

```cpp
dockercpp::DockerClient dockerclient;

// Verify Docker daemon is running
auto ping = dockerclient.pingCmd()->exec();
std::cout << "Docker is accessible: " << ping << std::endl;
```

### Working with Images

Pull and manage Docker images:

```cpp
dockercpp::DockerClient dockerclient;

// Pull an image
auto pulledImage = dockerclient.pullImageCmd("busybox")
    ->withTag("1.36")
    .exec();

// Inspect an image
auto imageInfo = dockerclient.inspectImageCmd("busybox:1.36")->exec();
std::cout << "Image ID: " << imageInfo.id << std::endl;
```

### Container Lifecycle Management

Create, start, stop, and remove containers:

```cpp
dockercpp::DockerClient dockerclient;

// Create a container with a name and command
auto response = dockerclient.createContainerCmd("busybox:1.36")
    ->withName("my-container")
    .withCmd(std::vector<std::string>{"sleep", "9999"})
    .exec();

std::cout << "Created container with ID: " << response.id << std::endl;

// Start the container
dockerclient.startContainerCmd(response.id)->exec();
std::cout << "Container started" << std::endl;

// Inspect running container to get details
auto inspectInfo = dockerclient.inspectContainerCmd(response.id)->exec();
std::cout << "Container running: " << inspectInfo.state.running << std::endl;
std::cout << "Container exit code: " << inspectInfo.state.exitCode << std::endl;

// Stop the running container
dockerclient.stopContainerCmd(response.id)->exec();
std::cout << "Container stopped" << std::endl;

// Inspect stopped container
auto stoppedInfo = dockerclient.inspectContainerCmd(response.id)->exec();
std::cout << "Container running (should be false): " << stoppedInfo.state.running << std::endl;

// Remove the container
dockerclient.removeContainerCmd(response.id)->exec();
std::cout << "Container removed" << std::endl;
```

### Getting Docker Information

Query Docker daemon information:

```cpp
dockercpp::DockerClient dockerclient;

// Get Docker version information
auto versionInfo = dockerclient.versionCmd()->exec();
std::cout << "Docker Version: " << versionInfo.version << std::endl;
std::cout << "API Version: " << versionInfo.apiVersion << std::endl;
std::cout << "OS: " << versionInfo.operatingSystem << std::endl;

// Get Docker system information
auto info = dockerclient.infoCmd()->exec();
std::cout << "Containers: " << info.containers << std::endl;
std::cout << "Images: " << info.images << std::endl;
std::cout << "Running: " << info.containersRunning << std::endl;
std::cout << "Stopped: " << info.containersStopped << std::endl;
```

