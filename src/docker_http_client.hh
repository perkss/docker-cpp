#ifndef SRC_DOCKER_HTTP_CLIENT_HPP
#define SRC_DOCKER_HTTP_CLIENT_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace dockercpp::transport::http {

class Response {
 public:
  Response(long status, std::unordered_map<std::string, std::string> headers,
           std::string body);

  long getStatusCode();
  std::unordered_map<std::string, std::string> getHeaders();

  std::string getHeader(std::string name);

  std::string getBody();

  ~Response();

 private:
  std::unordered_map<std::string, std::string> m_headers;
  long m_status;
  std::string m_body;
};

class RequestBuilder;

// https://github.com/docker-java/docker-java/blob/main/docker-java-transport/src/main/java/com/github/dockerjava/transport/DockerHttpClient.java#L47
class Request {
 public:
  enum class Method {
    GET,
    POST,
    PUT,
    DELETE,
    OPTIONS,
    PATCH,
  };

  friend class RequestBuilder;
  static RequestBuilder make();
  std::string method();
  std::string path();
  std::string body();
  std::unordered_map<std::string, std::vector<std::string>> headers();

 private:
  std::unordered_map<std::string, std::vector<std::string>> m_headers;
  std::string m_method;
  std::string m_body;
  std::string m_path;
};

class RequestBuilder {
 public:
  RequestBuilder& withMethod(Request::Method method);
  RequestBuilder& withBody(std::string body);
  RequestBuilder& withPath(std::string path);

  operator Request&&() { return std::move(m_request); }

 private:
  Request m_request;
};

class DockerHttpClient {
 public:
  virtual Response execute(Request request) = 0;
};
};  // namespace dockercpp::transport::http

#endif /* SRC_DOCKER_HTTP_CLIENT_HPP */
