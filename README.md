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


```
 dockercpp::DockerClient dockerclient;

  // Pull an image named busybox with version 1.36
  auto pulledImage =
      dockerclient.pullImageCmd("busybox")->withTag("1.36").exec();

  // Create the container with a name example and a command.
  auto response = dockerclient.createContainerCmd("busybox:1.36")
                      ->withName("example")
                      .withCmd(std::vector<std::string>{"sleep", "9999"})
                      .exec();

  auto startcontainer = dockerclient.startContainerCmd(response.id)->exec();

  auto inspectcontainer = dockerclient.inspectContainerCmd(response.id)->exec();

  auto stopcontainer = dockerclient.stopContainerCmd(response.id)->exec();

  // Check the container status now it is stopped
  auto inspectcontainerstopped =
      dockerclient.inspectContainerCmd(response.id)->exec();

  // Clean up the container by first deleting it and then removing the image
  auto deletecontainer = dockerclient.removeContainerCmd(response.id)->exec();

  auto deleteimage = dockerclient.removeImageCmd("busybox")->exec();
```
