class DockerCpp < Formula
  desc "Docker Client for C++"
  homepage "https://github.com/docker-cpp/docker-cpp"
  url "https://github.com/docker-cpp/docker-cpp/archive/v0.1.0.tar.gz"
  sha256 "PLACEHOLDER_SHA256_HASH"
  license "Apache-2.0"

  depends_on "cmake" => :build
  depends_on "ninja" => :build
  depends_on "boost"
  depends_on "curl"
  depends_on "spdlog"
  depends_on "nlohmann-json"

  def install
    args = %W[
      -DCMAKE_BUILD_TYPE=Release
      -DBUILD_TESTS=OFF
      -DBUILD_SHARED_LIBS=ON
      -DCMAKE_INSTALL_PREFIX=#{prefix}
      -G Ninja
    ]

    system "cmake", "-S", ".", "-B", "build", *args
    system "cmake", "--build", "build"
    system "cmake", "--install", "build"
  end

  test do
    # Simple test to verify the library is installed
    system "pkg-config", "--exists", "docker_cpp"
  end
end
