#include "exec_create_cmd_exec.hh"

#include <nlohmann/json.hpp>

#include "abstr_sync_docker_cmd_exec.hh"
#include "webtarget.hh"

namespace dockercpp::command::exec {

ExecCreateCmdExec::ExecCreateCmdExec()
    : AbstrSyncDockerCmdExec<ExecCreateCmd, ExecCreateResponse>(),
      CreateExec() {}

ExecCreateResponse ExecCreateCmdExec::exec(std::shared_ptr<ExecCreateCmd> command) {
    return execute(command);
}

ExecCreateResponse ExecCreateCmdExec::execute(std::shared_ptr<ExecCreateCmd> command) {
    core::WebTarget webResource = m_webTarget->path("containers")
                                            .path(command->getContainerId())
                                            .path("exec");

    nlohmann::json requestJson;
    requestJson["AttachStdin"] = command->isAttachStdin();
    requestJson["AttachStdout"] = command->isAttachStdout();
    requestJson["AttachStderr"] = command->isAttachStderr();
    requestJson["Tty"] = command->isTty();
    requestJson["Cmd"] = command->getCmd();

    if (!command->getUser().empty()) {
        requestJson["User"] = command->getUser();
    }
    requestJson["Privileged"] = command->isPrivileged();

    std::string requestStr = requestJson.dump();
    auto response = webResource.request().post(requestStr);

    spdlog::info("converting string {}", response);

    const nlohmann::json json = nlohmann::json::parse(response);
    ExecCreateResponse execResponse;
    execResponse.id = json.value("Id", "");
    execResponse.warnings = json.value("Warnings", nlohmann::json::array());

    return execResponse;
}

}  // namespace dockercpp::command::exec
