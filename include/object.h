#ifndef __object_h_
#define __object_h_

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

#ifdef _MSC_VER
# pragma warning(disable:4290)
#endif

enum {
  T_INTEGER,
  T_DOUBLE,
  T_STRING,
  T_BOOLEAN,
  T_CALLABLE,
  T_OBJECT
};

class Object {
  public:
    
    Object(int t);
    virtual ~Object();
    
    virtual Object* clone() const;
    
    virtual bool isCallable() const;
    virtual int call(class Stack *, bool &);
    
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    virtual bool equal(Object *rhs, bool &) const;
    virtual bool lessThan(Object *rhs, bool &) const;
    
    // ---
    
    inline bool notEqual(Object *rhs, bool &errored) const {
      return !equal(rhs, errored);
    }
    
    inline bool lessThanEqual(Object *rhs, bool &errored) const {
      bool rv = equal(rhs, errored);
      if (errored) {
        return rv;
      }
      return (rv || lessThan(rhs, errored));
    }
    
    inline bool greaterThan(Object *rhs, bool &errored) const {
      return !lessThanEqual(rhs, errored);
    }
    
    inline bool greaterThanEqual(Object *rhs, bool &errored) const {
      return !lessThan(rhs, errored);
    }
    
    inline int type() const {
      return mType;
    }
    
    inline void incRef() {
      ++mRef;
    }
    
    inline void decRef() {
      if (--mRef == 0) {
        delete this;
      }
    }
    
    inline long refCount() const {
      return mRef;
    }
    
    inline const std::string getError() const {
      return mErrString;
    }
  
  protected:
    
    inline void setError(const std::string &msg) const {
      mErrString = msg;
    }
    
  protected:
    
    int mType;
    
    long mRef;
    
    mutable std::string mErrString;
};

class Double : public Object {
  public:
    
    Double(double v = 0.0);
    virtual ~Double();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs, bool &) const;
    virtual bool lessThan(Object *rhs, bool &) const;
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    inline double getValue() const {
      return mValue;
    }
    
    inline void setValue(double v) {
      mValue = v;
    }
    
  protected:
    
    double mValue;
};

class Integer : public Object {
  public:
    
    Integer(long v = 0);
    virtual ~Integer();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs, bool &) const;
    virtual bool lessThan(Object *rhs, bool &) const;
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    inline long getValue() const {
      return mValue;
    }
    
    inline void setValue(long v) {
      mValue = v;
    }
    
  protected:
    
    long mValue;
};

class String : public Object {
  public:
    
    String(const std::string &v = "");
    virtual ~String();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs, bool &) const;
    virtual bool lessThan(Object *rhs, bool &) const;
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    inline const std::string& getValue() const {
      return mValue;
    }
    
    inline void setValue(const std::string &v) {
      mValue = v;
    }
    
  protected:
    
    std::string mValue;
};

class Boolean : public Object {
  public:
    
    Boolean(bool t=false);
    virtual ~Boolean();
    
    virtual Object* clone() const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    virtual bool equal(Object *rhs, bool &) const;
    virtual bool lessThan(Object *rhs, bool &) const;
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    inline bool getValue() const {
      return mValue;
    }
    
    inline void setValue(bool b) {
      mValue = b;
    }
    
  protected:
    
    bool mValue;
};

class Callable : public Object {
  public:
    
    Callable();
    virtual ~Callable();
    
    virtual bool isCallable() const;
    virtual bool lessThan(Object *rhs, bool &) const;
    virtual double toDouble(bool &) const;
    virtual long toInteger(bool &) const;
    virtual bool toBoolean(bool &) const;
    virtual std::string toString(bool &) const;
    
    class Context* context();
    class Context* getContext();
    void setContext(class Context *ctx);
    
  protected:
    
    class Context *mCtx;
};

class CFunction : public Callable {
  
  public:
    
    CFunction(int nargs, bool hasReturn);
    virtual ~CFunction();
    
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    int mNumArgs;
    bool mHasReturn;
};

class Block : public Callable {
  public:
    
    Block();
    virtual ~Block();
    
    virtual Object* clone() const;
    virtual int call(class Stack *stack, bool &errored);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    void addArgument(const std::string &name);
    void addInstruction(class Instruction *i);
    void setCode(class CodeSegment *);
    
    inline class CodeSegment* code() {
      return mCode;
    }
    
    inline const class CodeSegment* getCode() const {
      return mCode;
    }
    
  protected:
    
    class CodeSegment *mCode;
    std::vector<std::string> mArgs;
};

#endif
