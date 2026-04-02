#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <nlohmann/json.hpp>

// Include headers from installed docker-cpp
#include <docker_cpp/docker_client.hh>
#include <docker_cpp/ping_cmd.hh>
#include <docker_cpp/version_cmd.hh>
#include <docker_cpp/info_cmd.hh>
#include <docker_cpp/version.hh>

using json = nlohmann::json;

int main() {
    // Setup logging
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(console);
    
    console->info("=== docker-cpp Consumer Example ===");
    console->info("Library Version: {}.{}.{}", 
        DOCKER_CPP_VERSION_MAJOR,
        DOCKER_CPP_VERSION_MINOR, 
        DOCKER_CPP_VERSION_PATCH);
    
    try {
        // Create Docker client
        console->info("Creating Docker client...");
        dockercpp::DockerClient client;
        
        // Test 1: Ping
        console->info("\n[Test 1] Pinging Docker daemon...");
        dockercpp::PingCmd ping_cmd;
        ping_cmd.exec(client);
        console->info("✓ Docker daemon is responding");
        
        // Test 2: Get Version
        console->info("\n[Test 2] Getting Docker version...");
        dockercpp::VersionCmd version_cmd;
        auto version_info = version_cmd.exec(client);
        console->info("✓ Docker API Version: {}", version_info.apiVersion);
        console->info("  OS: {}", version_info.operatingSystem);
        
        // Test 3: Get Info
        console->info("\n[Test 3] Getting Docker info...");
        dockercpp::InfoCmd info_cmd;
        auto info = info_cmd.exec(client);
        console->info("✓ Docker Info retrieved");
        console->info("  Containers: {}", info.containers);
        console->info("  Images: {}", info.images);
        console->info("  Memory: {} MB", info.memoryTotal / (1024 * 1024));
        
        console->info("\n=== All tests passed successfully! ===");
        console->info("docker-cpp library integration complete.");
        
        return 0;
        
    } catch (const dockercpp::DockerException& e) {
        console->error("Docker exception: {}", e.what());
        return 1;
    } catch (const std::exception& e) {
        console->error("Standard exception: {}", e.what());
        return 1;
    }
}
