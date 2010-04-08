#include "context.h"
#include <sstream>
#include <algorithm>

Context::Context()
  : mParent(0), mCallStack(new CallStack()), mRef(1), mCallStackOwned(true) {
}

Context::Context(CallStack *cs)
  : mParent(0), mCallStack(cs), mRef(1), mCallStackOwned(false) {
}

Context::Context(Context *p)
  : mParent(p), mCallStack(p->getCallStack()), mRef(1), mCallStackOwned(false) {
  mParent->incRef();
  mParent->appendSub(this);
}

Context::~Context() {
  // if we come here, it means there's no more sub context
  // as each sub context has a strong reference on its parent
  clear();
  if (mCallStackOwned && mCallStack) {
    delete mCallStack;
    mCallStack = 0;
  }
  if (mParent) {
    mParent->removeSub(this);
    mParent->decRef();
    mParent = 0;
  }
}

void Context::appendSub(Context *ctx) {
  if (ctx != 0) {
    if (std::find(mSubs.begin(), mSubs.end(), ctx) == mSubs.end()) {
      mSubs.push_back(ctx);
    }
  }
}

void Context::removeSub(Context *ctx) {
  std::vector<Context*>::iterator it = std::find(mSubs.begin(), mSubs.end(), ctx);
  if (it != mSubs.end()) {
    mSubs.erase(it);
  }
}

void Context::cleanup() {
  incRef();
  clear();
  std::vector<Context*> subs;
  std::swap(mSubs, subs);
  for (size_t i=0; i<subs.size(); ++i) {
    subs[i]->cleanup();
  }
  decRef();
}

void Context::clear() {
  ObjectMap::iterator it = mVars.begin();
  while (it != mVars.end()) {
    if (it->second) {
      if (it->second->refCount() <= 0) {
        std::ostringstream oss;
        oss << "*** Object \"" << it->first << "\" in context has already been deleted";
        throw std::runtime_error(oss.str());
      }
      it->second->decRef();
    }
    ++it;
  }
}

bool Context::hasVar(const Symbol &name, bool inherit) const {
  if (mVars.find(name) != mVars.end()) {
    return true;
  } else if (mParent && inherit) {
    return mParent->hasVar(name, true);
  } else {
    return false;
  }
}

void Context::setVar(const Symbol &name, Object *v, bool inherit) {
  ObjectMap::iterator it = mVars.find(name);
  if (it != mVars.end()) {
    if (it->second != v) {
      it->second->decRef();
      it->second = v;
    } else {
      return;
    }
  } else {
    mVars[name] = v;
  }
  if (v) {
    v->incRef();
  }
}

Object* Context::getVar(const Symbol &name, bool inherit) const {
  ObjectMap::const_iterator it = mVars.find(name);
  if (it != mVars.end()) {
    Object *o = it->second;
    if (o) {
      o->incRef();
    }
    return o;
      
  } else {
    if (mParent && inherit) {
      return mParent->getVar(name);
    } else {
      return 0;
    }
  }
}

Callable* Context::getCallable(const Symbol &name, bool inherit) const {
  ObjectMap::const_iterator it = mVars.find(name);
  if (it != mVars.end() && it->second && it->second->isCallable()) {
    Object *o = it->second;
    if (o) {
      o->incRef();
    }
    return (Callable*) o;
    
  } else {
    if (mParent && inherit) {
      return mParent->getCallable(name);
    } else {
      return 0;
    }
  }
}

void Context::toStream(std::ostream &os, const std::string &indent) const {
  ObjectMap::const_iterator it = mVars.begin();
  while (it != mVars.end()) {
    os << indent << "\"" << it->first << "\" = ";
    it->second->toStream(os);
    os << std::endl;
    ++it;
  }
  if (mParent != 0) {
    os << indent << "From parent context:" << std::endl;
    mParent->toStream(os, indent+"  ");
  }
}
