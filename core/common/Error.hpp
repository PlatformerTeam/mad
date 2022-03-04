#ifndef MAD_ERROR_H
#define MAD_ERROR_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include <utility>
#include <sstream>

namespace mad::core {

void my_assert(bool value, const std::string& condition, const std::string& message, const std::string& file, int line);

enum class Status {
    Error,
    OutOfRange,
    InvalidArgument
};

struct Error : std::exception {
public:
    Error(Status status, std::string condition, std::string message, std::string file, int line);

    [[nodiscard]] const char *what() const noexcept override;

    Status status() const;

    std::string message() const;

    std::string condition() const;

    std::string where() const;

private:
    Status status_;
    std::string condition_;
    std::string message_;
    std::string file_;
    int line_;
    mutable std::string what_;
};

template <Status status_throw>
struct ThrowError : Error {
public:
    ThrowError(std::string condition, std::string message, std::string file, int line) :
    Error(status_throw, std::move(condition), std::move(message), std::move(file), line) {
    }
};

} // namespace mad::core

#define ASSERT(condition, message) \
    ::mad::core::my_assert(static_cast<bool>((condition)), #condition, message, __FILE__, __LINE__)

#define CHECK_THROW(condition, error_type, message)                                                                 \
    do {                                                                                                            \
        if (!static_cast<bool>((condition))) {                                                                      \
            throw ::mad::core::ThrowError<::mad::core::Status::error_type>(#condition, message, __FILE__, __LINE__);\
        }                                                                                                           \
    } while (0)

#endif //MAD_ERROR_H

