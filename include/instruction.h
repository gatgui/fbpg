#ifndef __instruction_h_
#define __instruction_h_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "stack.h"
#include "context.h"
#include "callstack.h"
#ifdef _MEMMGR
# include "heap.h"
#endif

enum {
  EVAL_FAILURE = -1,
  EVAL_NEXT = 0,
  EVAL_CONTINUE,
  EVAL_BREAK,
  EVAL_RETURN
};

#ifdef _MEMMGR
class Instruction : public HeapObject
#else
class Instruction
#endif
{
  public:
    
    Instruction(const Location &loc);
    virtual ~Instruction();
    
    virtual int eval(Stack *stack, Context *ctx) = 0;
    virtual Instruction* clone() const = 0;
    virtual void toStream(std::ostream &os, const std::string &heading="") const = 0;
    
    inline const Location& getLocation() const {
      return mLocation;
    }
    
  protected:
    
    Location mLocation;
};

class Push : public Instruction {
  public:
    
    Push(const Location &loc, Object *o);
    Push(const Location &loc, bool v);
    Push(const Location &loc, LongInteger v);
    Push(const Location &loc, double v);
    Push(const Location &loc, const char *v);
    Push(const Location &loc, const std::string &v);
    virtual ~Push();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    Object *mValue;
};

class Get : public Instruction {
  public:
    
    Get(const Location &loc, const std::string &name);
    virtual ~Get();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mName;
};

class Set : public Instruction {
  public:
    
    Set(const Location &loc, const std::string &name);
    virtual ~Set();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mName;
};

class Call : public Instruction {
  public:
    
    Call(const Location &loc, const std::string &name);
    virtual ~Call();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mFnName;
};

class If : public Instruction {
  public:
    
    If(const Location &loc, Block *cond, Block *code);
    virtual ~If();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack *stack, Context *ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mCode;
};

class IfElse : public Instruction {
  public:
    
    IfElse(const Location &loc, Block *cond, Block *ifCode, Block *elseCode);
    virtual ~IfElse();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack *stack, Context *ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mIfCode;
    Block *mElseCode;
};

class While : public Instruction {
  public:
    
    While(const Location &loc, Block *cond, Block *body);
    virtual ~While();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *stack, Context *ctx);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack *stack, Context *ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mBody;
};

class Break : public Instruction {
  public:
    
    Break(const Location &loc);
    virtual ~Break();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *, Context *);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class Continue : public Instruction {
  public:
    
    Continue(const Location &loc);
    virtual ~Continue();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *, Context *);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class Return : public Instruction {
  public:
    
    Return(const Location &loc);
    virtual ~Return();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *, Context *);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class DefFunc : public Instruction {
  public:
    
    DefFunc(const Location &loc, const std::string &name, Block *body);
    virtual ~DefFunc();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack *, Context *);
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mFnName;
    Block *mBody;
};

class CodeSegment : public std::vector<Instruction*> {
  public:
    
    CodeSegment();
    CodeSegment(const CodeSegment &rhs);
    virtual ~CodeSegment();
    
    CodeSegment& operator=(const CodeSegment &rhs);
    
    int eval(Stack *, Context *);
    
    void toStream(std::ostream &os, const std::string &heading="") const;
    
    inline void append(Instruction *i) {
      push_back(i);
    }
    
    inline void merge(CodeSegment *cs, bool rev=false) {
      if (cs->size() > 0) {
        if (rev) {
          for (size_t i=0; i<cs->size(); ++i) {
            push_back((*cs)[cs->size()-1-i]);
          }
        } else {
          for (size_t i=0; i<cs->size(); ++i) {
            push_back((*cs)[i]);
          }
        }
        cs->clear(); // not cleanup, we take ownership
      }
    }
    
    void cleanup();
    
    friend std::ostream& operator<<(std::ostream &, const CodeSegment &);
};


#endif
