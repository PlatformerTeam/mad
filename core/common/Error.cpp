#include <common/Error.h>

namespace mad::core {

void my_assert(bool value, const std::string& condition, const std::string& message, const std::string& file, int line) {
    if (!value) {
        std::cerr << "Error in " + file + ":" + std::to_string(line) + " with message: " + message + ". " + condition + " is false." << std::endl;
        std::exit(1);
    }
}

Error::Error(Status status, std::string condition, std::string message, std::string file, int line) :
    status_(status), condition_(std::move(condition)), message_(std::move(message)), file_(std::move(file)), line_(line) {
}

const char *Error::what() const noexcept {
    std::stringstream stream_what_;
    stream_what_ << "Throw error in " << file_ << ":" << std::to_string(line_) << " with message: " << message_ << ". " << condition_ << " is false.";
    what_ = stream_what_.str();
    return what_.c_str();
}

Status Error::status() const {
    return status_;
}

std::string Error::message() const {
    return message_;
}

std::string Error::condition() const {
    return condition_;
}

std::string Error::where() const {
    return file_ + ":" + std::to_string(line_);
}


} // namespace mad::core

