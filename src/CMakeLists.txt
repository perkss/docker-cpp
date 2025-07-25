add_library(docker_cpp_client
  create_container_cmd.cc
  create_container_response.cc
  create_container_cmd_exec.cc
  docker_client.cc
  docker_http_client.cc
  docker_object.cc
  curl_docker_http_client.cc
  docker_client_config.cc
  events_cmd.cc
  exec_create_cmd.cc
  exec_start_cmd.cc
  info_cmd.cc
  info_cmd_exec.cc
  info.cc
  inspect_container_cmd.cc
  inspect_image_cmd.cc
  inspect_container_response.cc
  inspect_image_response.cc
  inspect_container_cmd_exec.cc
  inspect_image_cmd_exec.cc
  ping_cmd_exec.cc
  ping_cmd.cc
  pull_image_cmd.cc
  pull_image_cmd_exec.cc
  search_images_cmd.cc
  stats_container_cmd.cc
  update_container_cmd.cc
  webtarget.cc
  abstr_sync_docker_cmd_exec.cc
  remove_container_cmd.cc
  remove_container_cmd_exec.cc
  remove_image_cmd.cc
  remove_image_cmd_exec.cc
  start_container_cmd.cc
  start_container_cmd_exec.cc
  stop_container_cmd.cc
  stop_container_cmd_exec.cc
  version.cc
  version_cmd.cc
  version_cmd_exec.cc
)

# is this needed?
target_include_directories(docker_cpp_client PUBLIC ../include
  create_container_cmd.hh
  create_container_response.hh
  create_container_cmd_exec.hh
  docker_object.hh
  docker_client.hh
  docker_http_client.hh
  curl_docker_http_client.hh
  info.hh
  inspect_container_cmd.hh
  inspect_container_cmd_exec.hh
  version.hh
  docker_cmd.hh
  docker_exception.hh
  ping_cmd.hh
  docker_client_config.hh
  pull_image_cmd.hh
  synch_docker_cmd.hh
  abstr_sync_docker_cmd_exec.hh
  webtarget.hh
  remove_image_cmd.hh
  remove_image_cmd_exec.hh
  start_container_cmd.hh
  start_container_cmd_exec.hh
  stop_container_cmd.hh
  stop_container_cmd_exec.hh
  ping_cmd_exec.hh
  version_cmd.hh
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


target_link_libraries(docker_cpp_client PRIVATE spdlog::spdlog curl  nlohmann_json::nlohmann_json ${Boost_LIBRARIES})

target_compile_features(docker_cpp_client PUBLIC cxx_std_20)
