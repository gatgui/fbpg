#ifndef __callstack_h_
#define __callstack_h_

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

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
    CallInfo(const Location &loc, const std::string &func);
    CallInfo(const CallInfo &rhs);
    ~CallInfo();
    
    CallInfo& operator=(const CallInfo &rhs);
    
    std::string toString() const;
    
  protected:
    
    Location mLocation;
    std::string mFuncname;
};

typedef std::vector<CallInfo> CallStack;

class Exception : public std::runtime_error {
  public:
    
    Exception(const CallStack &cs, const std::string &msg);
    virtual ~Exception() throw();
    
    virtual const char* what() const throw();
    
  protected:
    
    std::string mMessage;
    std::string mFullMessage;
};

#endif
