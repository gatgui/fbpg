#include "callstack.h"
#include <sstream>

// ---

CallInfo::CallInfo(const std::string &filename, int line, int col, const std::string &func)
  : mFilename(filename), mLine(line), mColumn(col), mFuncname(func) {
}

CallInfo::CallInfo(const CallInfo &rhs)
  : mFilename(rhs.mFilename), mLine(rhs.mLine), mColumn(rhs.mColumn),
    mFuncname(rhs.mFuncname) {
}

CallInfo::~CallInfo() {
}

CallInfo& CallInfo::operator=(const CallInfo &rhs) {
  if (this != &rhs) {
    mFilename = rhs.mFilename;
    mLine = rhs.mLine;
    mColumn = rhs.mColumn;
    mFuncname = rhs.mFuncname;
  }
  return *this;
}

std::string CallInfo::toString() const {
  std::ostringstream oss;
  oss << "From \"" << mFilename << "\", line " << mLine << ", column " << mColumn;
  if (mFuncname.length() > 0) {
    oss << ", in function \"" << mFuncname << "\"";
  }
  return oss.str();
}

// ---

Exception::Exception(const CallStack &cs, const std::string &msg)
  : std::runtime_error(msg), mMessage(msg) {
  mFullMessage = "*** Exception: ";
  mFullMessage += mMessage;
  for (size_t i=0; i<cs.size(); ++i) {
    mFullMessage += "\n  ";
    mFullMessage += cs[i].toString();
  }
}

Exception::~Exception() throw() {
}

const char* Exception::what() const throw() {
  return mFullMessage.c_str();
}
