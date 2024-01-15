#ifndef SRC_WEBTARGET_HPP
#define SRC_WEBTARGET_HPP

#include <string>
#include <unordered_map>

namespace dockercpp::core {

class InvocationBuilder {
 public:
  explicit InvocationBuilder(const std::string& path);

  std::string get();

  std::string post(std::string &json);

  bool deletehttp();

 private:
  std::string m_path;
};

class WebTarget {
 public:
  explicit WebTarget(const std::string& path) : m_path(path){};
  WebTarget(const std::string& path,
            const std::unordered_map<std::string, std::string>& queryParams);
  WebTarget path(const std::string& components);
  WebTarget queryParam(const std::string& name, const std::string& value);

  InvocationBuilder request();

 private:
  std::string m_path;
  std::unordered_map<std::string, std::string> m_queryParams;
};
}  // namespace dockercpp::core

#endif /* SRC_WEBTARGET_HPP */
