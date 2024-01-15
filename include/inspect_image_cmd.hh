#ifndef INCLUDE_INSPECT_IMAGE_CMD_HPP
#define INCLUDE_INSPECT_IMAGE_CMD_HPP

#include <memory>
#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "synch_docker_cmd.hh"

#include "inspect_image_response.hh"

namespace dockercpp::command {
class InspectImageCmd
    : public SynchDockerCmd<model::InspectImageResponse>,
      public std::enable_shared_from_this<InspectImageCmd> {
 public:
  virtual std::string getImageId() = 0;


};

namespace inspectimage {
class Exec : public exec::DockerCmdSyncExec<InspectImageCmd, model::InspectImageResponse> {
 public:
  ~Exec() {}
};
}  // namespace stopcontainer

class InspectImageCmdImpl
    : public InspectImageCmd,
      public AbstrDockerCmd<InspectImageCmd, model::InspectImageResponse> {
 public:
  explicit InspectImageCmdImpl(std::unique_ptr<inspectimage::Exec> exec,
                               const std::string& imageId);

  model::InspectImageResponse exec() override;

  void close() override {}

  std::string getImageId() override;

  ~InspectImageCmdImpl() override = default;

 private:
  std::string m_imageId;
};
}


#endif /* INCLUDE_INSPECT_IMAGE_CMD_HPP */
