#ifndef PULL_IMAGE_MD_H
#define PULL_IMAGE_MD_H


#include <memory>
#include <string>
#include <type_traits>

#include "abstr_sync_docker_cmd_exec.hh"

#include "docker_cmd.hh"
#include "synch_docker_cmd.hh"

namespace dockercpp::command {

// TODO this is an async example that needs sorting out
// https://github.com/docker-java/docker-java/blob/main/docker-java-core/src/main/java/com/github/dockerjava/core/exec/PullImageCmdExec.java
// https://github.com/docker-java/docker-java/blob/main/docker-java/src/test/java/com/github/dockerjava/cmd/PullImageCmdIT.java#L67
class PullImageCmd : public SynchDockerCmd<std::string>,
                     public std::enable_shared_from_this<PullImageCmd> {
 public:

    explicit PullImageCmd(const std::string& image);

      PullImageCmd& withTag(std::string tag);

  std::string getRepository();

  std::string getTag();

  std::string getRegistry();

    std::string getPlatform();

  ~PullImageCmd() {}

 private:
  std::string m_repository;
  std::string m_tag;
  std::string m_registry;
  std::string m_platform;
};

namespace pull {
class Exec : public exec::DockerCmdSyncExec<PullImageCmd, std::string> {
 public:
  ~Exec() {}
};
}  // namespace pull

class PullImageCmdImpl : public PullImageCmd,
                         public AbstrDockerCmd<PullImageCmd, std::string> {
 public:
    PullImageCmdImpl(std::unique_ptr<pull::Exec> exec, const std::string& image);

  std::string exec() override;

    void close() override;
    ~PullImageCmdImpl();
};

};  // namespace dockercpp::command
// https://stackoverflow.com/questions/51575956/libcurl-c-how-do-i-post-form-data-for-this-specific-form
//  TODO add function to create the form data style rather than the json body
//  https://docs.docker.com/engine/api/v1.43/#tag/Image/operation/ImageCreate
// cu rl --unix-socket /var/run/docker.sock \
//  -X POST "http://localhost/v1.43/images/create?fromImage=alpine"
#endif
