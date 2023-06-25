#ifndef SRC_CURL_DOCKER_HTTP_CLIENT_HPP
#define SRC_CURL_DOCKER_HTTP_CLIENT_HPP

#include "docker_http_client.hh"

namespace dockercpp::transport::http {

class Builder;

class CurlDockerHttpClient : public DockerHttpClient {
 public:
  friend class Builder;
  static Builder make();
  Response execute(Request request) override;

 private:
  CurlDockerHttpClient() = default;
  std::string m_dockerHost;
  int m_readTimeout;
  int m_connectTimeout;
};

class Builder {
 public:
  Builder& withDockerHost(std::string dockerHost);
  Builder& withReadTimeout(int readTimeout);
  Builder& withConnectTimeout(int connectTimeout);

  operator CurlDockerHttpClient&&() {
    return std::move(m_curlClientDockerClient);
  }

 private:
  CurlDockerHttpClient m_curlClientDockerClient;
};

};     // namespace dockercpp::transport::http
#endif /* SRC_CURL_DOCKER_HTTP_CLIENT_HPP */
