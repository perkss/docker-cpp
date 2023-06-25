#include "webtarget.hh"

#include <spdlog/spdlog.h>

#include <boost/algorithm/string/join.hpp>
#include <iterator>
#include <numeric>

#include "curl_docker_http_client.hh"
#include "docker_http_client.hh"

namespace dockercpp::core {

InvocationBuilder::InvocationBuilder(const std::string& path) : m_path(path) {}

std::string InvocationBuilder::get() {
  spdlog::info("get the request and send and get response");
  transport::http::Request request =
      transport::http::Request::make()
          .withMethod(transport::http::Request::Method::GET)
          .withPath(m_path);

  dockercpp::transport::http::CurlDockerHttpClient client =
      dockercpp::transport::http::CurlDockerHttpClient::make()
          .withDockerHost("")
          .withConnectTimeout(10)
          .withReadTimeout(10);

  return client.execute(request).getBody();
}

std::string InvocationBuilder::post(std::string& json) {
  spdlog::info("get the request and send and get response");
  transport::http::Request request =
      transport::http::Request::make()
          .withMethod(transport::http::Request::Method::POST)
          .withBody(json)
          .withPath(m_path);

  dockercpp::transport::http::CurlDockerHttpClient client =
      dockercpp::transport::http::CurlDockerHttpClient::make()
          .withDockerHost("")
          .withConnectTimeout(10)
          .withReadTimeout(10);

  return client.execute(request).getBody();
}

bool InvocationBuilder::deletehttp() {
  transport::http::Request request =
      transport::http::Request::make()
          .withMethod(transport::http::Request::Method::DELETE)
          .withPath(m_path);

  dockercpp::transport::http::CurlDockerHttpClient client =
      dockercpp::transport::http::CurlDockerHttpClient::make()
          .withDockerHost("")
          .withConnectTimeout(10)
          .withReadTimeout(10);

  // TODO sort return type
  client.execute(request);

  return true;
}

InvocationBuilder WebTarget::request() {
  std::vector<std::string> params;
  for (auto const& [key, val] : m_queryParams) {
    params.push_back(key + "=" + val);
  }

  auto resource = m_path;

  if (!params.empty()) {
    resource = resource + "?" + boost::algorithm::join(params, "&");
  }

  return InvocationBuilder(resource);
}

WebTarget WebTarget::path(const std::string& components) {
  spdlog::info("get a webtarget");
  return WebTarget(components);
}

WebTarget::WebTarget(
    const std::string& path,
    const std::unordered_map<std::string, std::string>& queryParams)
    : m_path(path), m_queryParams(queryParams){};

WebTarget WebTarget::queryParam(const std::string& name,
                                const std::string& value) {
  if (!value.empty() && !name.empty()) {
    m_queryParams.insert({name, value});
  }

  return WebTarget(m_path, m_queryParams);
}

}  // namespace dockercpp::core
