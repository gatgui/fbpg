#ifndef __callstack_h_
#define __callstack_h_

#include <string>
#include <vector>
#include "symbol.h"

class Location {
  public:
    
    Location();
    Location(const std::string &filename, int line, int col);
    Location(const Location &rhs);
    
    Location& operator=(const Location &rhs);
    
    std::string toString() const;
    
  protected:
    
    std::string mFilename;
    int mLine;
    int mColumn;
};

class CallInfo {
  public:
    
    CallInfo();
    CallInfo(const Location &loc, const Symbol &func);
    CallInfo(const CallInfo &rhs);
    ~CallInfo();
    
    CallInfo& operator=(const CallInfo &rhs);
    
    std::string toString() const;
    
  protected:
    
    Location mLocation;
    Symbol mFuncname;
};

class CallStack : public std::vector<CallInfo> {
  public:
    
    CallStack();
    CallStack(const CallStack &rhs);
    virtual ~CallStack();
    
    CallStack& operator=(const CallStack &rhs);
    
    std::string toString(const std::string &header="") const;
};

#endif
