#ifndef INCLUDE_DOCKER_CMD_HPP
#define INCLUDE_DOCKER_CMD_HPP


namespace dockercpp::command {
class DockerCmd {

  public:
    virtual void close() = 0;

    virtual ~DockerCmd() = default;

};
}


#endif /* INCLUDE_DOCKER_CMD_HPP */
