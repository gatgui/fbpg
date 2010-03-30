#ifndef __context_h_
#define __context_h_

#include "object.h"
#include "callstack.h"
#include <map>

class Context {
  public:
    
    typedef std::map<std::string, Object*> ObjectMap;
    
    Context();
    Context(CallStack *cs);
    Context(Context *p);
    ~Context();
    
    void clear();
    
    bool hasVar(const std::string &name, bool inherit=true) const;
    
    void setVar(const std::string &name, Object *v, bool inherit=true);
    
    Object* getVar(const std::string &name, bool inherit=true) const;
    Object* getCallable(const std::string &name, bool inherit=true) const;
    
    void toStream(std::ostream &os, const std::string &indent="") const;
    
    template <class FuncClass>
    void registerCFunction(const std::string &name) {
      CFunction *f = new FuncClass();
      f->setContext(this);
      setVar(name, f);
      f->decRef();
    }
    
    inline CallStack* getCallStack() {
      return mCallStack;
    }
    
    inline const CallStack* getCallStack() const {
      return mCallStack;
    }
    
    inline void incRef() {
      ++mRef;
    }
    
    inline void decRef() {
      if (--mRef == 0) {
        delete this;
      }
    }
    
  private:
    
    // Context();
    Context& operator=(Context &);
    
  protected:
    
    Context *mParent;
    ObjectMap mVars;
    CallStack *mCallStack;
    long mRef;
    bool mCallStackOwned;
};


#endif
