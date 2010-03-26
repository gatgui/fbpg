#include "context.h"
#include <sstream>

Context::Context(Context *p)
  : mParent(p) {
}

Context::~Context() {
  clear();
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
  mVars.clear();
}

bool Context::hasVar(const std::string &name, bool inherit) const {
  if (mVars.find(name) != mVars.end()) {
    return true;
  } else if (mParent && inherit) {
    return mParent->hasVar(name, true);
  } else {
    return false;
  }
}

void Context::setVar(const std::string &name, Object *v, bool inherit) {
  if (mParent && inherit && mParent->hasVar(name, true)) {
    mParent->setVar(name, v, true);
  }
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

Object* Context::getVar(const std::string &name, bool inherit) const {
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

Object* Context::getCallable(const std::string &name, bool inherit) const {
  ObjectMap::const_iterator it = mVars.find(name);
  if (it != mVars.end() && it->second->isCallable()) {
    Object *o = it->second;
    if (o) {
      o->incRef();
    }
    return o;
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
