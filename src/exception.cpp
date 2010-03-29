#include "exception.h"

Exception::Exception(const CallStack &cs, const std::string &msg)
  : std::exception(), mCallStack(cs), mMessage(msg) {
}

Exception::~Exception() throw() {
}

const char* Exception::what() const throw() {
  return mMessage.c_str();
}