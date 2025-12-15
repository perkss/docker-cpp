#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <streambuf>
#include <chrono>
#include <thread>

#include "docker_client.hh"
#include "inspect_image_cmd.hh"

namespace dockercpp::command::test {

class LoadImageCmdIT : public ::testing::Test {
 protected:
  void SetUp() override { dockerClient = std::make_unique<DockerClient>(); }

  void TearDown() override { dockerClient.reset(); }

  std::unique_ptr<DockerClient> dockerClient;
};

TEST_F(LoadImageCmdIT, loadImageFromTar) {
  // Build a tiny image, save it to tar, remove it, then load via API
  const std::string tmpdir = "/tmp/docker_cpp_load_test";
  system((std::string("rm -rf ") + tmpdir).c_str());
  system((std::string("mkdir -p ") + tmpdir).c_str());

  // Write a minimal Dockerfile
  std::ofstream df(tmpdir + "/Dockerfile");
  df << "FROM busybox\nCMD [\"/bin/sh\"]\n";
  df.close();

  // Build image
  int rc = system((std::string("docker build -t docker-cpp/load:1.0 ") + tmpdir + " > /dev/null").c_str());
  ASSERT_EQ(rc, 0);

  // Inspect to get image id
  auto info = dockerClient->inspectImageCmd("docker-cpp/load:1.0")->exec();
  ASSERT_FALSE(info.id.empty());
  std::string imageId = info.id;

  // Save to tar
  std::string tarPath = "/tmp/docker_cpp_load_image.tar";
  rc = system((std::string("docker save docker-cpp/load:1.0 -o ") + tarPath).c_str());
  ASSERT_EQ(rc, 0);

  // Remove image
  ASSERT_NO_THROW(dockerClient->removeImageCmd("docker-cpp/load:1.0")->withForce(true).exec());

  // Read tar into string
  std::ifstream ifs(tarPath, std::ios::binary);
  ASSERT_TRUE(ifs.good());
  std::string tarContents((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  ifs.close();

  // Load via our API
  ASSERT_NO_THROW(dockerClient->loadImageCmd(tarContents)->exec());

  // Allow Docker to register the image
  std::this_thread::sleep_for(std::chrono::seconds(3));

  // Verify image is present
  auto info2 = dockerClient->inspectImageCmd("docker-cpp/load:1.0")->exec();
  EXPECT_FALSE(info2.id.empty());
}

}  // namespace dockercpp::command::test
