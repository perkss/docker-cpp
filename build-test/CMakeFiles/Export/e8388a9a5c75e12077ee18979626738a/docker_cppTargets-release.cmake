#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "docker_cpp::docker_cpp_client" for configuration "Release"
set_property(TARGET docker_cpp::docker_cpp_client APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(docker_cpp::docker_cpp_client PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "spdlog::spdlog"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libdocker_cpp_client.0.1.0.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libdocker_cpp_client.0.dylib"
  )

list(APPEND _cmake_import_check_targets docker_cpp::docker_cpp_client )
list(APPEND _cmake_import_check_files_for_docker_cpp::docker_cpp_client "${_IMPORT_PREFIX}/lib/libdocker_cpp_client.0.1.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
