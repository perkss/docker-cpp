#include "curl_docker_http_client.hh"

#include <curl/curl.h>
#include <curl/easy.h>
#include <spdlog/spdlog.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "docker_http_client.hh"

enum { max_length = 1024 };

namespace dockercpp::transport::http {

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string *data) {
  data->append((char *)ptr, size * nmemb);
  return size * nmemb;
}

struct data {
  char trace_ascii; /* 1 or 0 */
};

static int my_trace(CURL *handle, curl_infotype type, char *data, size_t size,
                    void *userp) {
  std::string text;

  switch (type) {
    case CURLINFO_TEXT:
      spdlog::error("infoL {}", data);
    default:
      return 0;

    case CURLINFO_HEADER_OUT:
      text = "=> Send header";
      break;
    case CURLINFO_DATA_OUT:
      text = "=> Send data";
      break;
    case CURLINFO_SSL_DATA_OUT:
      text = "=> Send SSL data";
      break;
    case CURLINFO_HEADER_IN:
      text = "<= Recv header";
      break;
    case CURLINFO_DATA_IN:
      text = "<= Recv data";
      break;
    case CURLINFO_SSL_DATA_IN:
      text = "<= Recv SSL data";
      break;
  }

  spdlog::info("{}", text);
  return 0;
}

http::Response deletecurl(Request &request) {
  spdlog::info("Delete requested");
  auto curl = curl_easy_init();

  data config{};

  config.trace_ascii = 0; /* enable ascii tracing */

  if (!curl) {
  }

  const std::string requestUrl = "http://localhost/v1.42" + request.path();
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
  curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());
  curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");

  curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Accept: application/json");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  headers = curl_slist_append(headers, "charset: utf-8");

  std::string response_string;
  std::string header_string;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

  char *url;
  long response_code;
  double elapsed;

  curl_easy_perform(curl);
  
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
  curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
  curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

  curl_easy_cleanup(curl);
  curl = nullptr;

  spdlog::info("Response is {}", response_string);
  spdlog::info("Response header is {}", header_string);
  spdlog::info("Response code {}", response_code);

  http::Response response(response_code,
                          std::unordered_map<std::string, std::string>(),
                          response_string);
  return response;
}

http::Response postcurl(Request &request) {
  spdlog::info("Post requested");
  auto curl = curl_easy_init();
  data config;

  config.trace_ascii = 0; /* enable ascii tracing */
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    const std::string requestUrl = "http://localhost/v1.42" + request.path();
    spdlog::info("Request Url is {}", requestUrl);
    curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());

    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");

    std::string fields = request.body();

    if (request.body().empty()) {
      fields = "{}";
    }

    spdlog::info("About to send post: {}", request.body().c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

    curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8");

    std::string response_string;
    std::string header_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

    char *url;
    long response_code;
    double elapsed;

    curl_easy_perform(curl);
    
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

    curl_easy_cleanup(curl);
    curl = nullptr;
    spdlog::info("Response is {}", response_string);
    spdlog::info("Response code {}", response_code);
    spdlog::info("Response header is {}", header_string);

    http::Response response(response_code,
                            std::unordered_map<std::string, std::string>(),
                            response_string);
    return response;
  }

  throw std::invalid_argument("curl not initialized");
}

static size_t OnReceiveData(void *pData, size_t tSize, size_t tCount,
                            void *pmUser) {
  const size_t length = tSize * tCount;
  size_t index = 0;
  while (index < length) {
    const unsigned char *temp = static_cast<unsigned char *>(pData) + index;
    if ((temp[0] == '\r') || (temp[0] == '\n')) break;
    index++;
  }

  std::string str(static_cast<unsigned char *>(pData), static_cast<unsigned char *>(pData) + index);
  auto *pmHeader =
      static_cast<std::unordered_map<std::string, std::string> *>(pmUser);
  size_t pos = str.find(": ");
  if (pos != std::string::npos)
    pmHeader->insert(std::pair<std::string, std::string>(str.substr(0, pos),
                                                         str.substr(pos + 2)));

  return (tCount);
}

http::Response requestcurl(const std::string &path) {
  auto curl = curl_easy_init();
  if (curl) {
    const std::string requestUrl = "http://localhost/" + path;
    spdlog::info("Request Url is {}", requestUrl);
    curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

    std::string response_string;
    std::string header_string;
    std::unordered_map<std::string, std::string> headers;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, OnReceiveData);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);

    char *url;
    long response_code;
    double elapsed;

    curl_easy_perform(curl);

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

    curl_easy_cleanup(curl);
    curl = nullptr;

    spdlog::info("Response is code={}, body={}", response_code,
                 response_string);
    spdlog::info("Header is {}", headers.size());

    http::Response response =
        http::Response(response_code, headers, response_string);

    return response;
  }

  std::unordered_map<std::string, std::string> headers;
  http::Response response = http::Response(500l, headers, "");

  return response;
}

Response CurlDockerHttpClient::execute(Request request) {
  if (request.method() == "POST") {
    return postcurl(request);
  } else if (request.method() == "GET") {
    return requestcurl(request.path());
  } else if (request.method() == "DELETE") {
    return deletecurl(request);
  } else {
    throw 1;
  }
}

Builder CurlDockerHttpClient::make() { return {}; }

Builder &Builder::withDockerHost(std::string dockerHost) {
  m_curlClientDockerClient.m_dockerHost = std::move(dockerHost);
  return *this;
}

Builder &Builder::withReadTimeout(int readTimeout) {
  m_curlClientDockerClient.m_readTimeout = readTimeout;
  return *this;
}

Builder &Builder::withConnectTimeout(int connectTimeout) {
  m_curlClientDockerClient.m_connectTimeout = connectTimeout;
  return *this;
}

};  // namespace dockercpp::transport::http
