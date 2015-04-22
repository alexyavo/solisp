#pragma once

#include <exception>

namespace utils {

class BufferUnderflowException : public std::exception {};

}
