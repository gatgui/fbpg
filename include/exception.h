#ifndef __exception_h_
#define __exception_h_

#include "callstack.h"
#include <exception>
#include <stdexcept>

class Exception : public std::exception {
  public:
    
    Exception(const std::string &msg, const CallStack *cs);
    virtual ~Exception() throw();
    
    virtual const char* what() const throw();
    
    inline const CallStack* getCallStack() const {
      return mCallStack;
    }
    
  protected:
    
    const CallStack *mCallStack;
    std::string mMessage;
};

#endif
