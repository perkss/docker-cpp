// https://riptutorial.com/cplusplus/example/30166/builder-pattern-with-fluent-api
#include "docker_client_config.hh"

#include <spdlog/spdlog.h>

#include <memory>
#include <unordered_set>

namespace dockercpp::core {

const std::string DOCKER_HOST = "DOCKER_HOST";
const std::string DOCKER_CONTEXT = "DOCKER_CONTEXT";
const std::string DOCKER_TLS_VERIFY = "DOCKER_TLS_VERIFY";
const std::string DOCKER_CONFIG = "DOCKER_CONFIG";
const std::string DOCKER_CERT_PATH = "DOCKER_CERT_PATH";
const std::string API_VERSION = "api.version";
const std::string REGISTRY_USERNAME = "registry.username";
const std::string REGISTRY_PASSWORD = "registry.password";
const std::string REGISTRY_EMAIL = "registry.email";
const std::string REGISTRY_URL = "registry.url";

namespace {

std::unordered_set<std::string> configKeys{
    DOCKER_HOST,   DOCKER_CERT_PATH, DOCKER_CONTEXT, DOCKER_TLS_VERIFY,
    DOCKER_CONFIG, API_VERSION,      REGISTRY_EMAIL, REGISTRY_PASSWORD,
    REGISTRY_URL,  REGISTRY_USERNAME};

const std::string DEFAULT_DOCKER_HOST = "unix:///var/run/docker.sock";
const std::string WINDOWS_DEFAULT_DOCKER_HOST =
    "npipe:////./pipe/docker_engine";
};  // namespace

std::string DefaultDockerClientConfig::getDockerHost() { return m_dockerHost; }

std::string DefaultDockerClientConfig::getRegistryUsername() {
  return m_registryUsername;
}

std::string DefaultDockerClientConfig::getRegistryPassword() {
  return m_registryPassword;
}

std::string DefaultDockerClientConfig::getRegistryEmail() {
  return m_registryEmail;
}

std::string DefaultDockerClientConfig::getRegistryUrl() {
  return m_registryUrl;
}

Builder& Builder::withDockerHost(std::string dockerHost) {
  m_dockerconfig.m_dockerHost = dockerHost;
  return *this;
}
Builder& Builder::withRegistryUsername(std::string username) {
  m_dockerconfig.m_registryUsername = username;
  return *this;
}
Builder& Builder::withRegistryPassword(std::string password) {
  m_dockerconfig.m_registryPassword = password;
  return *this;
}
Builder& Builder::withRegistryEmail(std::string email) {
  m_dockerconfig.m_registryEmail = email;
  return *this;
}
Builder& Builder::withRegistryUrl(std::string url) {
  // test passing by reference
  m_dockerconfig.m_registryUrl = url;
  return *this;
}

Builder DefaultDockerClientConfig::make() {
  spdlog::info("Make default client config builder");
  return Builder();
}

}  // namespace dockercpp::core
