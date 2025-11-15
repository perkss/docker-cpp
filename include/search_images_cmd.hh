#ifndef SEARCH_IMAGES_CMD_HPP
#define SEARCH_IMAGES_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct SearchItem {
    std::string description;
    bool is_official;
    bool is_automated;
    std::string name;
    int64_t star_count;
};

class SearchImagesCmd : public SynchDockerCmd<std::vector<SearchItem>>,
                       public std::enable_shared_from_this<SearchImagesCmd> {
 public:
  virtual std::string getTerm() const = 0;
  virtual SearchImagesCmd& withTerm(const std::string& term) = 0;
  virtual int getLimit() const = 0;
  virtual SearchImagesCmd& withLimit(int limit) = 0;
};

namespace search {
class Exec : public exec::DockerCmdSyncExec<SearchImagesCmd, std::vector<SearchItem>> {
 public:
  ~Exec() {}
};
}  // namespace search

class SearchImagesCmdImpl : public SearchImagesCmd,
                          public AbstrDockerCmd<SearchImagesCmd, std::vector<SearchItem>> {
 public:
  explicit SearchImagesCmdImpl(std::unique_ptr<search::Exec> exec);

  std::vector<SearchItem> exec() override;

  void close() override {}

  std::string getTerm() const override;
  SearchImagesCmd& withTerm(const std::string& term) override;
  int getLimit() const override;
  SearchImagesCmd& withLimit(int limit) override;

  ~SearchImagesCmdImpl() {}

 private:
  std::string m_term;
  int m_limit;
};

}  // namespace dockercpp::command
#endif /* SEARCH_IMAGES_CMD_HPP */
