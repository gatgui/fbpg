#include "context.h"
#include <sstream>
#include <algorithm>

#ifndef _SYMTBL

Context::ObjectMap::ObjectMap() {
}

Context::ObjectMap::ObjectMap(const Context::ObjectMap &rhs)
  : Context::ObjectMap::MapType(rhs) {
}

Context::ObjectMap::~ObjectMap() {
}

Context::ObjectMap& Context::ObjectMap::operator=(const Context::ObjectMap &rhs) {
  Context::ObjectMap::MapType::operator=(rhs);
  return *this;
}

void Context::ObjectMap::insert(const Context::ObjectMap::KeyType &key, const Context::ObjectMap::ValueType &val) {
  (*this)[key] = val;
}

void Context::ObjectMap::erase(const Context::ObjectMap::KeyType &k) {
  MapType::iterator it = find(k);
  if (it != end()) {
    MapType::erase(it);
  }
}

bool Context::ObjectMap::hasKey(const Context::ObjectMap::KeyType &key) const {
  return (find(key) != end());
}

const Context::ObjectMap::ValueType& Context::ObjectMap::getValue(const Context::ObjectMap::KeyType &k) const {
  MapType::const_iterator it = find(k);
  if (it == end()) {
    std::ostringstream oss;
    oss << "Invalid key: \"" << k << "\"";
    throw std::runtime_error(oss.str());
  }
  return it->second;
}

Context::ObjectMap::ValueType& Context::ObjectMap::getValue(const Context::ObjectMap::KeyType &k) {
  MapType::iterator it = find(k);
  if (it == end()) {
    std::ostringstream oss;
    oss << "Invalid key: \"" << k << "\"";
    throw std::runtime_error(oss.str());
  }
  return it->second;
}

bool Context::ObjectMap::getValue(const Context::ObjectMap::KeyType &k, Context::ObjectMap::ValueType &v) const {
  MapType::const_iterator it = find(k);
  if (it == end()) {
    return false;
  } else {
    v = it->second;
    return true;
  }
}

size_t Context::ObjectMap::getKeys(Context::ObjectMap::KeyVector &kl) const {
  kl.resize(size());
  MapType::const_iterator it = begin();
  for (size_t i=0; i<size(); ++i, ++it) {
    kl[i] = it->first;
  }
  return size();
}

size_t Context::ObjectMap::getValues(Context::ObjectMap::ValueVector &vl) const {
  vl.resize(size());
  MapType::const_iterator it = begin();
  for (size_t i=0; i<size(); ++i, ++it) {
    vl[i] = it->second;
  }
  return size();
}

size_t Context::ObjectMap::getPairs(Context::ObjectMap::KeyValueVector &kvl) const {
  kvl.resize(size());
  MapType::const_iterator it = begin();
  for (size_t i=0; i<size(); ++i, ++it) {
    kvl[i] = KeyValuePair(it->first, it->second);
  }
  return size();
}

#endif

// ---

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
  /*
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
  */
  std::vector<Symbol> keys;
  std::vector<Object*> values;
  size_t n = mVars.getKeys(keys);
  mVars.getValues(values);
  for (size_t i=0; i<n; ++i) {
    if (values[i]) {
      if (values[i]->refCount() <= 0) {
        std::ostringstream oss;
        oss << "*** Object \"" << keys[i] << "\" in context has already been deleted";
        throw std::runtime_error(oss.str());
      }
      values[i]->decRef();
    }
  }
  mVars.clear();
}

bool Context::hasVar(const Symbol &name, bool inherit) const {
  //if (mVars.find(name) != mVars.end()) {
  if (mVars.hasKey(name)) {
    return true;
  } else if (mParent && inherit) {
    return mParent->hasVar(name, true);
  } else {
    return false;
  }
}

void Context::setVar(const Symbol &name, Object *v, bool inherit) {
  if (mParent && inherit && mParent->hasVar(name, true)) {
    mParent->setVar(name, v, true);
  }
  Object *oldVal = 0;
  if (mVars.getValue(name, oldVal)) {
    if (oldVal) {
      oldVal->decRef();
    }
  }
  mVars.insert(name, v);
  /*
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
  */
  if (v) {
    v->incRef();
  }
}

Object* Context::getVar(const Symbol &name, bool inherit) const {
  /*
  ObjectMap::const_iterator it = mVars.find(name);
  if (it != mVars.end()) {
    Object *o = it->second;
    if (o) {
      o->incRef();
    }
    return o;
  */
  Object *o = 0;
  if (mVars.getValue(name, o)) {
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
  /*
  ObjectMap::const_iterator it = mVars.find(name);
  if (it != mVars.end() && it->second->isCallable()) {
    Object *o = it->second;
    if (o) {
      o->incRef();
    }
    return (Callable*) o;
  */
  Object *o = 0;
  if (mVars.getValue(name, o) && o && o->isCallable()) {
    o->incRef();
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
  /*
  ObjectMap::const_iterator it = mVars.begin();
  while (it != mVars.end()) {
    os << indent << "\"" << it->first << "\" = ";
    it->second->toStream(os);
    os << std::endl;
    ++it;
  }
  */
  ObjectMap::KeyValueVector kvl;
  size_t n = mVars.getPairs(kvl);
  for (size_t i=0; i<n; ++i) {
    os << indent << "\"" << kvl[i].first << "\" = ";
    if (kvl[i].second) {
      kvl[i].second->toStream(os);
    } else {
      os << "<Null>";
    }
    os << std::endl;
  }
  if (mParent != 0) {
    os << indent << "From parent context:" << std::endl;
    mParent->toStream(os, indent+"  ");
  }
}
