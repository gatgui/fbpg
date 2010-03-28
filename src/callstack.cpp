#include "callstack.h"
#include <sstream>

// ---

Location::Location()
  : mFilename(""), mLine(0), mColumn(0) {
}

Location::Location(const std::string &filename, int line, int col)
  : mFilename(filename), mLine(line), mColumn(col) {
}

Location::Location(const Location &rhs)
  : mFilename(rhs.mFilename), mLine(rhs.mLine), mColumn(rhs.mColumn) {
}

Location& Location::operator=(const Location &rhs) {
  if (this != &rhs) {
    mFilename = rhs.mFilename;
    mLine = rhs.mLine;
    mColumn = rhs.mColumn;
  }
  return *this;
}

std::string Location::toString() const {
  std::ostringstream oss;
  oss << "file \"" << mFilename << "\", line " << mLine << ", column " << mColumn;
  return oss.str();
}

// ---

CallInfo::CallInfo()
  : mFuncname("") {
}

CallInfo::CallInfo(const Location &loc, const std::string &func)
  : mLocation(loc), mFuncname(func) {
}

CallInfo::CallInfo(const CallInfo &rhs)
  : mLocation(rhs.mLocation), mFuncname(rhs.mFuncname) {
}

CallInfo::~CallInfo() {
}

CallInfo& CallInfo::operator=(const CallInfo &rhs) {
  if (this != &rhs) {
    mLocation = rhs.mLocation;
    mFuncname = rhs.mFuncname;
  }
  return *this;
}

std::string CallInfo::toString() const {
  std::ostringstream oss;
  oss << "From " << mLocation.toString();
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
