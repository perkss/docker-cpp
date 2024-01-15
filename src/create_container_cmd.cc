#include "create_container_cmd.hh"

#include <vector>

namespace dockercpp::command {

CreateContainerCmd& CreateContainerCmd::withName(const std::string& name) {
  request.name = name;
  return *this;
}

CreateContainerCmd& CreateContainerCmd::withHost(const std::string& name) {
  request.hostName = name;
  return *this;
}

CreateContainerCmd& CreateContainerCmd::withCmd(const std::string& cmd) {
  request.cmd.push_back(cmd);
  return *this;
}

CreateContainerCmd& CreateContainerCmd::withCmd(
    const std::vector<std::string>& cmd) {
  request.cmd.insert(std::end(request.cmd), std::begin(cmd), std::end(cmd));
  return *this;
}

CreateContainerCmdImpl::CreateContainerCmdImpl(
    std::unique_ptr<createcontainer::Exec> exec, std::string image)
    : AbstrDockerCmd<CreateContainerCmd, model::CreateContainerResponse>(
          std::move(exec)) {
  request.imageName = image;
}

model::CreateContainerResponse CreateContainerCmdImpl::exec() {
  return m_execution->exec(shared_from_this());
}

void to_json(nlohmann::json& j,
             const CreateContainerRequest& createContainerRequest) {
  j["Image"] = createContainerRequest.imageName;

  if (!createContainerRequest.hostName.empty()) {
    j["Hostname"] = createContainerRequest.hostName;
  }

  if (!createContainerRequest.cmd.empty()) {
    j["Cmd"] = createContainerRequest.cmd;
  }
}

}  // namespace dockercpp::command
