#ifndef __context_h_
#define __context_h_

#include "object.h"
#include <map>

class Context {
  public:
    
    typedef std::map<std::string, Object*> ObjectMap;
    
    Context(Context *p = 0);
    ~Context();
    
    void clear();
    
    bool hasVar(const std::string &name, bool inherit=true) const;
    
    void setVar(const std::string &name, Object *v, bool inherit=true);
    
    Object* getVar(const std::string &name, bool inherit=true) const;
    Object* getCallable(const std::string &name, bool inherit=true) const;
    
    void toStream(std::ostream &os, const std::string &indent="") const;
    
  protected:
    
    Context *mParent;
    ObjectMap mVars;
};

#endif
