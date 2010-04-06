#ifndef __context_h_
#define __context_h_

#include "object.h"
#include "callstack.h"
#include <map>
#include <vector>
#ifdef _SYMTBL
# include "symbol.h"
typedef Symbol ContextKey;
#else
typedef std::string ContextKey;
#endif

class Context {
  public:
    
    typedef std::map<ContextKey, Object*> ObjectMap;
    
    Context();
    Context(CallStack *cs);
    Context(Context *p);
    ~Context();
    
    void clear();
    void cleanup();
    
    bool hasVar(const ContextKey &name, bool inherit=true) const;
    
    void setVar(const ContextKey &name, Object *v, bool inherit=true);
    
    Object* getVar(const ContextKey &name, bool inherit=true) const;
    Callable* getCallable(const ContextKey &name, bool inherit=true) const;
    
    void toStream(std::ostream &os, const std::string &indent="") const;
    
    template <class FuncClass>
    void registerCFunction(const ContextKey &name) {
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
    
    inline int getDepth() const {
      int depth = 0;
      Context *p = mParent;
      while (p) {
        depth += 1;
        p = p->mParent;
      }
      return depth;
    }
  
  protected:
    
    void appendSub(Context *ctx);
    void removeSub(Context *ctx);
    
  private:
    
    // Context();
    Context& operator=(Context &);
    
  protected:
    
    Context *mParent;
    ObjectMap mVars;
    CallStack *mCallStack;
    long mRef;
    bool mCallStackOwned;
    std::vector<Context*> mSubs;
};


#endif
