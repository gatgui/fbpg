#ifndef __instruction_h_
#define __instruction_h_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "stack.h"
#include "context.h"


enum {
  EVAL_NEXT = 0,
  EVAL_CONTINUE,
  EVAL_BREAK,
  EVAL_RETURN
};

class Instruction {
  public:
    
    Instruction();
    virtual ~Instruction();
    
    virtual int eval(Stack &stack, Context &ctx) = 0;
    virtual Instruction* clone() const = 0;
    virtual int stackConsumption(Context &) const = 0;
    virtual void toStream(std::ostream &os, const std::string &heading="") const = 0;
};

class Push : public Instruction {
  public:
    
    Push(Object *o);
    Push(bool v);
    Push(long v);
    Push(double v);
    Push(const char *v);
    Push(const std::string &v);
    virtual ~Push();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    Object *mValue;
};

class Get : public Instruction {
  public:
    
    Get(const std::string &name);
    virtual ~Get();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mName;
};

class Set : public Instruction {
  public:
    
    Set(const std::string &name);
    virtual ~Set();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mName;
};

class Call : public Instruction {
  public:
    
    Call(const std::string &name);
    virtual ~Call();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
  protected:
    
    std::string mFnName;
};

class If : public Instruction {
  public:
    
    If(Block *cond, Block *code);
    virtual ~If();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack &stack, Context &ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mCode;
};

class IfElse : public Instruction {
  public:
    
    IfElse(Block *cond, Block *ifCode, Block *elseCode);
    virtual ~IfElse();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack &stack, Context &ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mIfCode;
    Block *mElseCode;
};

class While : public Instruction {
  public:
    
    While(Block *cond, Block *body);
    virtual ~While();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &stack, Context &ctx);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
    
    bool evalCondition(Stack &stack, Context &ctx) const;
    
  protected:
    
    Block *mCond;
    Block *mBody;
};

class Break : public Instruction {
  public:
    
    Break();
    virtual ~Break();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &, Context &);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class Continue : public Instruction {
  public:
    
    Continue();
    virtual ~Continue();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &, Context &);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class Return : public Instruction {
  public:
    
    Return();
    virtual ~Return();
    
    virtual Instruction* clone() const;
    virtual int eval(Stack &, Context &);
    virtual int stackConsumption(Context &) const;
    virtual void toStream(std::ostream &os, const std::string &heading="") const;
};

class CodeSegment : public std::vector<Instruction*> {
  public:
    
    CodeSegment();
    CodeSegment(const CodeSegment &rhs);
    virtual ~CodeSegment();
    
    CodeSegment& operator=(const CodeSegment &rhs);
    
    int eval(Stack &, Context &);
    
    int stackConsumption(Context &) const;
    
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
