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
  events_cmd_exec.cc
  exec_create_cmd.cc
  exec_create_cmd_exec.cc
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
  load_image_cmd.cc
  load_image_cmd_exec.cc
  abstr_sync_docker_cmd_exec.cc
  remove_container_cmd.cc
  remove_container_cmd_exec.cc
  remove_image_cmd.cc
  remove_image_cmd_exec.cc
  start_container_cmd.cc
  start_container_cmd_exec.cc
  stop_container_cmd.cc
  stop_container_cmd_exec.cc
  update_container_cmd_exec.cc
  update_container_cmd.cc
  version.cc
  version_cmd.cc
  version_cmd_exec.cc
)

# Set public include directories
target_include_directories(docker_cpp_client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  $<INSTALL_INTERFACE:include>
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)


target_link_libraries(docker_cpp_client PRIVATE spdlog::spdlog curl  nlohmann_json::nlohmann_json ${Boost_LIBRARIES})

target_compile_features(docker_cpp_client PUBLIC cxx_std_20)

# Set library version properties
set_target_properties(docker_cpp_client PROPERTIES
  VERSION ${DOCKER_CPP_VERSION_STRING}
  SOVERSION ${DOCKER_CPP_VERSION_MAJOR}
  PUBLIC_HEADER "../include/docker_client.hh"
)

# Install library
install(
  TARGETS docker_cpp_client
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
