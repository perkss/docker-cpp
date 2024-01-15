#ifndef SRC_DOCKER_CLIENT_CONFIG_HPP
#define SRC_DOCKER_CLIENT_CONFIG_HPP

#include <string>

namespace dockercpp::core {

class DockerClientConfig {
 public:
  virtual std::string getDockerHost() = 0;
  virtual std::string getRegistryUsername() = 0;
  virtual std::string getRegistryPassword() = 0;
  virtual std::string getRegistryEmail() = 0;
  virtual std::string getRegistryUrl() = 0;
  virtual ~DockerClientConfig() = default;
};

class Builder;

class DefaultDockerClientConfig : DockerClientConfig {
 public:
  friend class Builder;
  static Builder make();

  std::string getDockerHost() override;
  std::string getRegistryUsername() override;
  std::string getRegistryPassword() override;
  std::string getRegistryEmail() override;
  std::string getRegistryUrl() override;

  ~DefaultDockerClientConfig() override = default;

 private:
  DefaultDockerClientConfig() = default;

  std::string m_dockerHost;
  std::string m_registryUsername;
  std::string m_registryPassword;
  std::string m_registryEmail;
  std::string m_registryUrl;
};

class Builder {
 public:
  Builder& withDockerHost(const std::string& dockerHost);
  Builder& withRegistryUsername(const std::string& username);
  Builder& withRegistryPassword(const std::string& password);
  Builder& withRegistryEmail(const std::string& email);
  Builder& withRegistryUrl(const std::string& url);

  operator DefaultDockerClientConfig&&() { return std::move(m_dockerconfig); }

 private:
  DefaultDockerClientConfig m_dockerconfig;
};

}  // namespace dockercpp::core

#endif /* SRC_DOCKER_CLIENT_CONFIG_HPP */
