#include "object.h"
#include "instruction.h"
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

unsigned long gNumObjects = 0;

Object::Object(int t)
  : mType(t), mRef(1) {
  ++gNumObjects;
}

Object::~Object() {
  --gNumObjects;
#ifdef _DEBUG
  if (gNumObjects == 0) {
    std::cout << "### All object deleted" << std::endl;
  }
#endif
}

bool Object::equal(Object *rhs, bool &errored) const {
  errored = false;
  return (this == rhs);
}

bool Object::lessThan(Object *rhs, bool &errored) const {
  errored = false;
  return ((void*)this < (void*)rhs);
}

Object* Object::clone() const {
  return new Object(mType);
}

bool Object::isCallable() const {
  return false;
}

int Object::call(Stack *, Context *, bool &errored) {
  errored = true;
  setError("Object is not callable");
  return EVAL_FAILURE;
}

void Object::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "<Object: 0x" << std::hex << (void*)this << std::dec << ">";
}

double Object::toDouble(bool &err) const {
  err = false;
  return 0.0;
}

LongInteger Object::toInteger(bool &err) const {
  err = false;
  return 0;
}

bool Object::toBoolean(bool &err) const {
  err = false;
  return false;
}

std::string Object::toString(bool &err) const {
  err = false;
  return "";
}

// ---

Double::Double(double v)
  : Object(T_DOUBLE), mValue(v) {
}

Double::~Double() {
}

Object* Double::clone() const {
  return new Double(mValue);
}

void Double::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool Double::equal(Object *rhs, bool &err) const {
  double drhs = rhs->toDouble(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue == drhs);
}

bool Double::lessThan(Object *rhs, bool &err) const {
  double drhs = rhs->toDouble(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue < drhs);
}

double Double::toDouble(bool &err) const {
  err = false;
  return mValue;
}

LongInteger Double::toInteger(bool &err) const {
  err = false;
  return LongInteger(mValue);
}

bool Double::toBoolean(bool &err) const {
  err = false;
  return (mValue != 0.0);
}

std::string Double::toString(bool &err) const {
  std::ostringstream oss;
  err = false;
  oss << mValue;
  return oss.str();
}

// ---

Integer::Integer(LongInteger v)
  : Object(T_INTEGER), mValue(v) {
}

Integer::~Integer() {
}

Object* Integer::clone() const {
  return new Integer(mValue);
}

void Integer::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool Integer::equal(Object *rhs, bool &err) const {
  LongInteger irhs = rhs->toInteger(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue == irhs);
}

bool Integer::lessThan(Object *rhs, bool &err) const {
  LongInteger irhs = rhs->toInteger(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue < irhs);
}

double Integer::toDouble(bool &err) const {
  err = false;
  return double(mValue);
}

LongInteger Integer::toInteger(bool &err) const {
  err = false;
  return mValue;
}

bool Integer::toBoolean(bool &err) const {
  err = false;
  return (mValue != 0);
}

std::string Integer::toString(bool &err) const {
  err = false;
  std::ostringstream oss;
  oss << mValue;
  return oss.str();
}

// ---

String::String(const std::string &v)
  : Object(T_STRING), mValue(v) {
}

String::~String() {
}

Object* String::clone() const {
  return new String(mValue);
}

void String::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << mValue;
}

bool String::equal(Object *rhs, bool &err) const {
  std::string srhs = rhs->toString(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue == srhs);
}

bool String::lessThan(Object *rhs, bool &err) const {
  std::string srhs = rhs->toString(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (strcmp(mValue.c_str(), srhs.c_str()) < 0);
}

double String::toDouble(bool &err) const {
  double v = 0.0;
  if (sscanf(mValue.c_str(), "%lf", &v) != 1) {
    err = true;
    setError("String not convertible to double");
  } else {
    err = false;
  }
  return v;
}

LongInteger String::toInteger(bool &err) const {
  LongInteger v = 0;
  if (sscanf(mValue.c_str(), "%lld", &v) != 1) {
    err = true;
    setError("String not convertible to integer");
  } else {
    err = false;
  }
  return v;
}

bool String::toBoolean(bool &err) const {
  err = false;
  return (mValue.length() > 0);
}

std::string String::toString(bool &err) const {
  err = false;
  return mValue;
}


// ---

Boolean::Boolean(bool v)
  : Object(T_BOOLEAN), mValue(v) {
}

Boolean::~Boolean() {
}

Object* Boolean::clone() const {
  return new Boolean(mValue);
}

void Boolean::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << (mValue ? "true" : "false");
}

bool Boolean::equal(Object *rhs, bool &err) const {
  bool brhs = rhs->toBoolean(err);
  if (err) {
    setError(rhs->getError());
    return false;
  }
  return (mValue == brhs);
}

bool Boolean::lessThan(Object *, bool &err) const {
  err = true;
  setError("Boolean object are not comparable");
  return false;
}

double Boolean::toDouble(bool &err) const {
  err = false;
  return (mValue ? 1.0 : 0.0);
}

LongInteger Boolean::toInteger(bool &err) const {
  err = false;
  return (mValue ? 1 : 0);
}

bool Boolean::toBoolean(bool &err) const {
  err = false;
  return mValue;
}

std::string Boolean::toString(bool &err) const {
  err = false;
  return (mValue ? "true" : "false");
}

// ---

Callable::Callable()
  : Object(T_CALLABLE), mCtx(0) {
}

Callable::~Callable() {
  if (mCtx) {
    mCtx->decRef();
  }
}

Context* Callable::getContext() {
  if (mCtx) {
    mCtx->incRef();
    return mCtx;
  } else {
    return 0;
  }
}

void Callable::setContext(Context *ctx) {
  if (mCtx) {
    mCtx->decRef();
  }
  mCtx = ctx;
  if (mCtx) {
    mCtx->incRef();
  }
}

bool Callable::isCallable() const {
  return true;
}

bool Callable::lessThan(Object *, bool &err) const {
  err = true;
  setError("Callable object are not comparable");
  return false;
}

double Callable::toDouble(bool &err) const {
  err = true;
  setError("Callable cannot be converted to a double");
  return 0.0;
}

LongInteger Callable::toInteger(bool &err) const {
  err = true;
  setError("Callable cannot be converted to an integer");
  return 0;
}

bool Callable::toBoolean(bool &err) const {
  err = true;
  setError("Callable cannot be converted to a boolean");
  return false;
}

std::string Callable::toString(bool &err) const {
  err = true;
  setError("Callable cannot be converted to a string");
  return "";
}

// ---

CFunction::CFunction(int nargs, bool hasReturn)
  : Callable(), mNumArgs(nargs), mHasReturn(hasReturn) {
}

CFunction::~CFunction() {
}

void CFunction::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "<CFunction: 0x" << std::hex << (void*)this << std::dec << ">";
}

// ---

Block::Block()
  : Callable(), mCode(0) {
}

Block::~Block() {
  if (mCode != 0) {
    delete mCode;
    mCode = 0;
  }
}

void Block::addArgument(const std::string &name) {
  mArgs.push_back(name);
}

void Block::addInstruction(Instruction *i) {
  if (mCode == 0) {
    mCode = new CodeSegment();
  }
  mCode->push_back(i);
}

void Block::setCode(CodeSegment *cs) {
  if (mCode != 0) {
    delete mCode;
  }
  mCode = cs;
}

Object* Block::clone() const {
  Block *b = new Block();
  for (size_t i=0; i<mArgs.size(); ++i) {
    b->addArgument(mArgs[i]);
  }
  if (mCode != 0) {
    b->setCode(new CodeSegment(*mCode));
  }
  // shall I?
  //if (mCtx != 0) {
  //  b->setContext(mCtx);
  //}
  return b;
}

int Block::call(Stack *stack, Context *ctx, bool &err) {
  err = false;
  if (mCode == 0) {
    return EVAL_NEXT;
  }
  int numArgs = int(mArgs.size());
  for (int i=numArgs-1; i>=0; --i) {
    Object *o = stack->pop();
    if (!o) {
      err = true;
      setError("Not enough arguments on stack");
      return EVAL_FAILURE;
    }
    ctx->setVar(mArgs[i], o);
    o->decRef();
  }
  int rv = mCode->eval(stack, ctx);
  return rv;
}

void Block::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "{Block:";
  if (mArgs.size() > 0) {
    os << " (";
    for (size_t i=0; i<mArgs.size()-1; ++i) {
      os << mArgs[i] << ", ";
    }
    os << mArgs.back() << ")";
  }
  os << std::endl;
  if (mCode != 0) {
    //os << std::endl;
    mCode->toStream(os, heading + "  ");
    os << std::endl;
  }
  os << heading << "}";
  //os << " >";
}

