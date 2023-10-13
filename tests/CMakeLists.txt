include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        docker_cpp_client_test
        docker_client_test.cc
        curl_docker_http_client_test.cc
        create_container_response_test.cc
        create_container_cmd_test.cc
        inspect_container_response_test.cc
        remove_image_cmd_exec_test.cc
        version_test.cc
      )

# add required local or remote libraries here
target_link_libraries(
        docker_cpp_client_test
        docker_cpp_client
        gtest_main
        gmock
        curl
        nlohmann_json::nlohmann_json
        ${Boost_LIBRARIES}
        spdlog::spdlog
)

target_compile_features(docker_cpp_client_test PUBLIC cxx_std_20)

set(CTEST_OUTPUT_ON_FAILURE, ON)

include(GoogleTest)
gtest_discover_tests(docker_cpp_client_test)
