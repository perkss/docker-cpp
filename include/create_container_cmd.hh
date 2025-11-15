#ifndef INCLUDE_CREATE_CONTAINER_CMD_HPP
#define INCLUDE_CREATE_CONTAINER_CMD_HPP

#include <memory>
#include <map>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "create_container_response.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

struct CreateContainerRequest {
  std::string imageName;
  std::string hostName;
  std::string name;
  std::vector<std::string> cmd;
  std::map<std::string, std::string> labels;
};

struct HostConfig {
  std::string hostName;
};

class CreateContainerCmd
    : public SynchDockerCmd<model::CreateContainerResponse>,
      public std::enable_shared_from_this<CreateContainerCmd> {
 public:
  CreateContainerCmd& withName(const std::string& name);

  CreateContainerCmd& withHost(const std::string& name);

  CreateContainerCmd& withCmd(const std::string& cmd);

  CreateContainerCmd& withCmd(const std::vector<std::string>& cmd);

  CreateContainerCmd& withLabels(const std::map<std::string, std::string>& labels);

  CreateContainerCmd& withLabel(const std::string& key, const std::string& value);

  CreateContainerRequest getRequest() { return request; }

  ~CreateContainerCmd() override = default;

 protected:
  CreateContainerRequest request;
};

namespace createcontainer {
class Exec : public exec::DockerCmdSyncExec<CreateContainerCmd,
                                            model::CreateContainerResponse> {
 public:
  ~Exec() override = default;
};
}  // namespace createcontainer

class CreateContainerCmdImpl
    : public CreateContainerCmd,
      public AbstrDockerCmd<CreateContainerCmd,
                            model::CreateContainerResponse> {
 public:
  explicit CreateContainerCmdImpl(std::unique_ptr<createcontainer::Exec> exec,
                                  std::string image);

  model::CreateContainerResponse exec() override;

  void close() override {}

  ~CreateContainerCmdImpl() {}
};

void to_json(nlohmann::json& j,
             const CreateContainerRequest& createContainerRequest);

}  // namespace dockercpp::command

#endif /* INCLUDE_CREATE_CONTAINER_CMD_HPP */
