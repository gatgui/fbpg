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
    oss << ": function \"" << mFuncname << "\"";
  }
  return oss.str();
}

// ---

CallStack::CallStack() {
}

CallStack::CallStack(const CallStack &rhs)
  : std::vector<CallInfo>(rhs) {
}
  
CallStack::~CallStack() {
}

CallStack& CallStack::operator=(const CallStack &rhs) {
  std::vector<CallInfo>::operator=(rhs);
  return *this;
}

std::string CallStack::toString(const std::string &header) const {
  std::string s;
  if (size() > 0) {
    s += header + (*this)[0].toString();
    for (size_t i=1; i<size(); ++i) {
      s += "\n";
      s += header + (*this)[i].toString();
    }
  }
  return s;
}

