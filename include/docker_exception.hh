#ifndef DOCKER_EXCEPTION_H
#define DOCKER_EXCEPTION_H

#include <exception>
#include <string>

namespace dockercpp {

class DockerException : public std::runtime_error {
public:
    DockerException(const std::string& message) 
        : std::runtime_error(message), statusCode_(0) {}
        
    DockerException(const std::string& message, int statusCode)
        : std::runtime_error(message), statusCode_(statusCode) {}

    DockerException(const std::string& message, int statusCode, const std::string& responseBody)
        : std::runtime_error(message), 
          statusCode_(statusCode), 
          responseBody_(responseBody) {}

    int getStatusCode() const { return statusCode_; }
    const std::string& getResponseBody() const { return responseBody_; }

private:
    int statusCode_;
    std::string responseBody_;
};

// Specific Docker exceptions
class DockerClientException : public DockerException {
public:
    explicit DockerClientException(const std::string& message)
        : DockerException(message) {}
};

class NotModifiedException : public DockerException {
public:
    NotModifiedException(const std::string& message)
        : DockerException(message, 304) {}
};

class NotFoundException : public DockerException {
public:
    NotFoundException(const std::string& message)
        : DockerException(message, 404) {}
};

class ConflictException : public DockerException {
public:
    ConflictException(const std::string& message)
        : DockerException(message, 409) {}
};

class InternalServerErrorException : public DockerException {
public:
    InternalServerErrorException(const std::string& message)
        : DockerException(message, 500) {}
};

} // namespace dockercpp

#endif
