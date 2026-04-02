# Packaging Guide for docker-cpp

This document describes how to build, package, and distribute docker-cpp for different platforms.

## Build Configuration

The project uses CMake with configurable options for packaging:

- `CMAKE_BUILD_TYPE`: Set to `Release` for production packages (default: `Release`)
- `BUILD_SHARED_LIBS`: Build shared library (default: `ON`)
- `BUILD_TESTS`: Include test suite (default: `ON`, set to `OFF` for packages)

### Release Build Example

```bash
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_SHARED_LIBS=ON -G Ninja -S . -B build
cmake --build build
cmake --install build
```

## Ubuntu/Debian Packaging

### Building a .deb Package

```bash
# Install build dependencies
sudo apt-get install debhelper cmake g++ libboost-all-dev libcurl4-openssl-dev libspdlog-dev nlohmann-json3-dev ninja-build

# Build the package
debuild -us -uc

# Or using dpkg-buildpackage
dpkg-buildpackage -us -uc
```

### Install from .deb

```bash
sudo dpkg -i libdocker-cpp0_0.1.0-1_amd64.deb
sudo dpkg -i libdocker-cpp-dev_0.1.0-1_amd64.deb
```

### Debian Package Contents

- **libdocker-cpp0**: Runtime library (`libdocker_cpp_client.so.0`)
- **libdocker-cpp-dev**: Development headers, CMake configs, pkg-config file

## macOS/Homebrew Packaging

### Building from Formula

```bash
# Test the formula locally
brew install --build-from-source ./Formula/docker-cpp.rb

# Or use the GitHub tap (once published)
brew install docker-cpp/core/docker-cpp
```

### Formula Requirements

- Must pass `brew audit formula`
- Dependencies automatically installed
- Formula located in `Formula/docker-cpp.rb`

## Installation Verification

After installation, verify the package is correctly installed:

```bash
# Check pkg-config
pkg-config --cflags --libs docker_cpp

# Verify CMake integration (Linux/macOS)
cmake -E capabilities | grep -i docker_cpp

# Check installed files
dpkg -L libdocker-cpp-dev    # Debian
brew list docker-cpp         # Homebrew
```

## For Downstream Projects

Once installed via package manager, downstream projects can use:

```cmake
# CMake
find_package(docker_cpp REQUIRED)
target_link_libraries(my_app docker_cpp::docker_cpp)

# Or pkg-config
pkg-config --cflags --libs docker_cpp
```

## Release Process

1. Update version in `CMakeLists.txt`
2. Update `debian/changelog` with release notes
3. Create git tag: `git tag -a v0.1.0 -m "Release v0.1.0"`
4. Build packages for platforms
5. Upload to package repositories (Launchpad PPA, Homebrew, etc.)

## Publishing to Homebrew Core

1. Fork [homebrew-core](https://github.com/Homebrew/homebrew-core)
2. Update `Formula/docker-cpp.rb` with correct SHA256
3. Run `brew audit --strict Formula/docker-cpp.rb`
4. Submit pull request with justification

## CI/CD Integration

GitHub Actions workflows handle automated package building:

- `.github/workflows/build_cmake.yml` - Build and test
- `.github/workflows/release.yml` - Build release packages on tags

