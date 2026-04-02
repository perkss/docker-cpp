#ifndef DOCKER_CPP_VERSION_HH
#define DOCKER_CPP_VERSION_HH

#include <string>

namespace dockercpp {

// Semantic versioning constants
constexpr int DOCKER_CPP_VERSION_MAJOR = 0;
constexpr int DOCKER_CPP_VERSION_MINOR = 1;
constexpr int DOCKER_CPP_VERSION_PATCH = 0;

// Version string: "major.minor.patch"
constexpr const char* DOCKER_CPP_VERSION_STRING = "0.1.0";

// Utility function to get version string
inline std::string getVersion() {
  return DOCKER_CPP_VERSION_STRING;
}

// Utility function to get version as tuple (major, minor, patch)
inline std::tuple<int, int, int> getVersionTuple() {
  return std::make_tuple(DOCKER_CPP_VERSION_MAJOR, DOCKER_CPP_VERSION_MINOR,
                        DOCKER_CPP_VERSION_PATCH);
}

}  // namespace dockercpp

#endif /* DOCKER_CPP_VERSION_HH */
