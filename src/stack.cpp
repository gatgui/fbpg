#include "stack.h"
#include <sstream>

Stack::Stack() {
}

Stack::~Stack() {
  clear();
}

int Stack::size() const {
  return int(mStack.size());
}

void Stack::clear() {
  while (size() > 0) {
    Object *o = pop();
    if (o->refCount() <= 0) {
       std::ostringstream oss;
      oss << "*** Object on stack at position " << size() << " has already been deleted";
      throw std::runtime_error(oss.str());
    }
    o->decRef();
  }
}

bool Stack::push(Object *o) {
  if (!o) {
    setError("Pushed null object on stack");
    return false;
  }
  o->incRef();
  mStack.push_back(o);
  return true;
}

void Stack::pushBoolean(bool v) {
  push(new Boolean(v));
}

void Stack::pushInteger(long v) {
  push(new Integer(v));
}

void Stack::pushDouble(double v) {
  push(new Double(v));
}

void Stack::pushString(const std::string &v) {
  push(new String(v));
}

Object* Stack::pop(int n) {
  Object *rv = 0;
  Object *o = 0;
  if (n <= 0) {
    std::ostringstream oss;
    oss << "Stack::pop: Invalid argument: " << n;
    setError(oss.str());
    return rv;
  }
  while (n > 0 && mStack.size() > 0) {
    o = mStack.back();
    if (rv == 0) {
      rv = o;
    }
    if (o) {
      o->decRef();
    }
    mStack.pop_back();
    --n;
  }
  return rv;
}

bool Stack::popBoolean(bool &err) {
  Object *o = pop();
  if (o == 0) {
    err = true;
    setError("Null object on stack");
    return false;
  }
  bool rv = o->toBoolean(err);
  o->decRef();
  return rv;
}

long Stack::popInteger(bool &err) {
  Object *o = pop();
  if (o == 0) {
    err = true;
    setError("Null object on stack");
    return false;
  }
  long rv = o->toInteger(err);
  o->decRef();
  return rv;
}

double Stack::popDouble(bool &err) {
  Object *o = pop();
  if (o == 0) {
    err = true;
    setError("Null object on stack");
    return false;
  }
  double rv = o->toDouble(err);
  o->decRef();
  return rv;
}

std::string Stack::popString(bool &err) {
  Object *o = pop();
  if (o == 0) {
    err = true;
    setError("Null object on stack");
    return false;
  }
  std::string rv = o->toString(err);
  o->decRef();
  return rv;
}

Object* Stack::get(int idx) const {
  if (idx < 0) {
    idx = size() + idx;
    if (idx < 0) {
      std::ostringstream oss;
      oss << "Stack::get: Invalid index: " << idx;
      setError(oss.str());
      return 0;
    }
  }
  if (idx >= size()) {
    std::ostringstream oss;
    oss << "Stack::get: Invalid index: " << idx;
    setError(oss.str());
    return 0;
  }
  return mStack[idx];
}

bool Stack::getBoolean(int idx, bool &err) const {
  Object *o = get(idx);
  if (o == 0) {
    err = true;
    return false;
  }
  return (o->toBoolean(err));
}

long Stack::getInteger(int idx, bool &err) const {
  Object *o = get(idx);
  if (o == 0) {
    err = true;
    return 0;
  }
  return (o->toInteger(err));
}

double Stack::getDouble(int idx, bool &err) const {
  Object *o = get(idx);
  if (o == 0) {
    err = true;
    return 0.0;
  }
  return (o->toDouble(err));
}

std::string Stack::getString(int idx, bool &err) const {
  Object *o = get(idx);
  if (o == 0) {
    err = true;
    return "";
  }
  return (o->toString(err));
}

