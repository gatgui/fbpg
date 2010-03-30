#include "exception.h"

Exception::Exception(const std::string &msg, const CallStack *cs)
  : std::exception(), mCallStack(cs), mMessage(msg) {
}

Exception::~Exception() throw() {
}

const char* Exception::what() const throw() {
  return mMessage.c_str();
}