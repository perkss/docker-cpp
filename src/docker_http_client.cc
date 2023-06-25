#include "docker_http_client.hh"

namespace dockercpp::transport::http {

namespace {

const std::string methodToString(Request::Method e) {
  switch (e) {
    case Request::Method::GET:
      return "GET";
    case Request::Method::POST:
      return "POST";
    case Request::Method::PUT:
      return "PUT";
    case Request::Method::DELETE:
      return "DELETE";
    case Request::Method::OPTIONS:
      return "OPTIONS";
    case Request::Method::PATCH:
      return "PATCH";

    default:
      throw std::invalid_argument("Unimplemented item");
  }
}

}  // namespace

Response::Response(long status,
                   std::unordered_map<std::string, std::string> headers,
                   std::string body)
    : m_status(status), m_headers(headers), m_body(body) {}

long Response::getStatusCode() { return m_status; }

std::unordered_map<std::string, std::string> Response::getHeaders() {
  return m_headers;
}

std::string Response::getBody() { return m_body; }

std::string Response::getHeader(std::string name) { return m_headers[name]; }

Response::~Response() {}

std::string Request::method() { return m_method; }

std::string Request::path() { return m_path; }

std::string Request::body() { return m_body; }

RequestBuilder Request::make() { return RequestBuilder(); }

std::unordered_map<std::string, std::vector<std::string>> Request::headers() {
  return m_headers;
}

RequestBuilder& RequestBuilder::withPath(std::string path) {
  m_request.m_path = path;
  return *this;
}

RequestBuilder& RequestBuilder::withBody(std::string body) {
  m_request.m_body = body;
  return *this;
}

RequestBuilder& RequestBuilder::withMethod(Request::Method method) {
  m_request.m_method = http::methodToString(method);
  return *this;
}

}  // namespace dockercpp::transport::http
