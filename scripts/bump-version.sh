#!/bin/bash
# Script to bump the version number for docker-cpp
# Usage: ./scripts/bump-version.sh 0.2.0

set -e

if [ -z "$1" ]; then
  echo "Usage: $0 <new-version>"
  echo "Example: $0 0.2.0"
  exit 1
fi

NEW_VERSION="$1"
MAJOR=$(echo $NEW_VERSION | cut -d. -f1)
MINOR=$(echo $NEW_VERSION | cut -d. -f2)
PATCH=$(echo $NEW_VERSION | cut -d. -f3)

echo "Bumping version to $NEW_VERSION..."

# Update CMakeLists.txt
sed -i.bak "s/set(DOCKER_CPP_VERSION_MAJOR [0-9]*)/set(DOCKER_CPP_VERSION_MAJOR $MAJOR)/" CMakeLists.txt
sed -i.bak "s/set(DOCKER_CPP_VERSION_MINOR [0-9]*)/set(DOCKER_CPP_VERSION_MINOR $MINOR)/" CMakeLists.txt
sed -i.bak "s/set(DOCKER_CPP_VERSION_PATCH [0-9]*)/set(DOCKER_CPP_VERSION_PATCH $PATCH)/" CMakeLists.txt
rm CMakeLists.txt.bak

# Update version.hh
sed -i.bak "s/constexpr int DOCKER_CPP_VERSION_MAJOR = [0-9]*;/constexpr int DOCKER_CPP_VERSION_MAJOR = $MAJOR;/" include/docker_cpp/version.hh
sed -i.bak "s/constexpr int DOCKER_CPP_VERSION_MINOR = [0-9]*;/constexpr int DOCKER_CPP_VERSION_MINOR = $MINOR;/" include/docker_cpp/version.hh
sed -i.bak "s/constexpr int DOCKER_CPP_VERSION_PATCH = [0-9]*;/constexpr int DOCKER_CPP_VERSION_PATCH = $PATCH;/" include/docker_cpp/version.hh
sed -i.bak "s/constexpr const char\\* DOCKER_CPP_VERSION_STRING = \"[^\"]*\";/constexpr const char* DOCKER_CPP_VERSION_STRING = \"$NEW_VERSION\";/" include/docker_cpp/version.hh
rm include/docker_cpp/version.hh.bak

# Update debian/changelog
if [ "$(uname)" == "Darwin" ]; then
  DATE=$(date -u +"%a, %d %b %Y %H:%M:%S +0000")
else
  DATE=$(date -u -R)
fi
sed -i.bak "1s/^/docker-cpp ($NEW_VERSION-1) unstable; urgency=low\n\n  * Version $NEW_VERSION release\n\n -- docker-cpp Contributors <you@example.com>  $DATE\n\n/" debian/changelog
rm debian/changelog.bak

echo "Version bumped to $NEW_VERSION"
echo "Don't forget to:"
echo "  1. Review changes"
echo "  2. Commit: git commit -am 'Bump version to $NEW_VERSION'"
echo "  3. Tag: git tag -a v$NEW_VERSION -m 'Release v$NEW_VERSION'"
