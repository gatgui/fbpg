#include "instruction.h"

unsigned long gNumInstructions = 0;

Instruction::Instruction() {
  ++gNumInstructions;
}

Instruction::~Instruction() {
  --gNumInstructions;
  if (gNumInstructions == 0) {
    std::cout << "### All instructions deleted" << std::endl;
  }
}

// ---

Push::Push(Object *o)
  : Instruction(), mValue(o) {
}

Push::Push(bool v)
  : Instruction(), mValue(new Boolean(v)) {
}

Push::Push(long v)
  : Instruction(), mValue(new Integer(v)) {
}

Push::Push(double v)
  : Instruction(), mValue(new Double(v)) {
}

Push::Push(const char *v)
  : Instruction(), mValue(new String(v)) {
}

Push::Push(const std::string &v)
  : Instruction(), mValue(new String(v)) {
}

Push::~Push() {
  mValue->decRef();
}

Instruction* Push::clone() const {
  return new Push(mValue->clone());
}

int Push::stackConsumption(Context &) const {
  return 1;
}

int Push::eval(Stack &stack, Context &) {
  // need an additonal incRef here or when decRef is called on the popped value from the stack
  // (as it should always be the case) we end up deleting the object.
  mValue->incRef();
  stack.push(mValue);
  return EVAL_NEXT;
}

void Push::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Push" << std::endl;
  if (mValue->type() == T_STRING) {
    mValue->toStream(os, heading+"  \"");
    os << "\"";
  } else {
    mValue->toStream(os, heading+"  ");
  }
}

// ---

Get::Get(const std::string &name)
  : Instruction(), mName(name) {
}

Get::~Get() {
}

Instruction* Get::clone() const {
  return new Get(mName);
}

int Get::stackConsumption(Context &) const {
  return 1;
}

int Get::eval(Stack &stack, Context &ctx) {
  Object *o = ctx.getVar(mName);
  stack.push(o);
  // Do not decRef, objects on stack must have at least double reference
  // not to be destroyed when popped
  //o->decRef();
  return EVAL_NEXT;
}

void Get::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Get \"" << mName << "\"";
}

// ---

Set::Set(const std::string &name)
  : Instruction(), mName(name) {
}

Set::~Set() {
}

Instruction* Set::clone() const {
  return new Set(mName);
}

int Set::stackConsumption(Context &) const {
  return -1;
}

int Set::eval(Stack &stack, Context &ctx) {
  Object *o = stack.pop();
  ctx.setVar(mName, o);
  o->decRef();
  return EVAL_NEXT;
}

void Set::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Set \"" << mName << "\"";
}

// ---

Call::Call(const std::string &name)
  : Instruction(), mFnName(name) {
}

Call::~Call() {
}

Instruction* Call::clone() const {
  return new Call(mFnName);
}

int Call::stackConsumption(Context &ctx) const {
	// this one sucks... should it be hard-coded?
	// what if there are reference to not yet defined functions...
  Object *o = ctx.getCallable(mFnName);
  if (o == NULL) {
    return 0;
  } else {
    int n = ((Callable*)o)->stackConsumption(ctx);
    o->decRef();
    return n;
  }
}

int Call::eval(Stack &stack, Context &ctx) {
  Object *o = ctx.getCallable(mFnName);
  if (o == NULL) {
    throw std::runtime_error("No \""+mFnName+"\" function defined");
  }
  //return o->call(stack, ctx);
  o->call(stack, ctx);
  o->decRef();
  return EVAL_NEXT;
}

void Call::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Call \"" << mFnName << "\"";
}

// ---

If::If(Block *cond, Block *code)
  : Instruction(), mCond(cond), mCode(code) {
}

If::~If() {
  if (mCond) {
    mCond->decRef();
    mCond = 0;
  }
  if (mCode) {
    mCode->decRef();
    mCode = 0;
  }
}

Instruction* If::clone() const {
  return new If((mCond ? (Block*)mCond->clone() : 0), (mCode ? (Block*)mCode->clone() : 0));
}

int If::stackConsumption(Context &ctx) const {
  if (mCode != 0) {
    int sc = mCode->stackConsumption(ctx);
    if (sc != 0) {
      throw std::runtime_error("\"if\" statement body must leave stack globaly unchanged");
    }
  }
  return 0;
}

bool If::evalCondition(Stack &stack, Context &ctx) const {
  if (mCond == 0) {
    throw std::runtime_error("Missing condition for \"if\" statement");
  }
  int sz = stack.size();
  mCond->call(stack, ctx);
  if (stack.size() - sz != 1) {
    throw std::runtime_error("Detected stack corruption while evaluating \"if\" condition");
  }
  return stack.popBoolean();
}

int If::eval(Stack &stack, Context &ctx) {
  if (evalCondition(stack, ctx)) {
    if (mCode) {
      Context ictx(&ctx);
      return mCode->call(stack, ictx);
    }
  }
  return EVAL_NEXT;
}

void If::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "If";
  if (mCond) {
    os << std::endl;
    mCond->toStream(os, heading+"  ");
  }
  os << std::endl << heading << "Then";
  if (mCode) {
    os << std::endl;
    mCode->toStream(os, heading+"  ");
  }
}

// ---

IfElse::IfElse(Block *cond, Block *ifCode, Block *elseCode)
  : Instruction(), mCond(cond), mIfCode(ifCode), mElseCode(elseCode) {
}

IfElse::~IfElse() {
  if (mCond) {
    mCond->decRef();
    mCond = 0;
  }
  if (mIfCode) {
    mIfCode->decRef();
    mIfCode = 0;
  }
  if (mElseCode) {
    mElseCode->decRef();
    mElseCode = 0;
  }
}

Instruction* IfElse::clone() const {
  return new IfElse((mCond ? (Block*)mCond->clone() : 0),
                    (mIfCode ? (Block*)mIfCode->clone() : 0),
                    (mElseCode ? (Block*)mElseCode->clone() : 0));
}

int IfElse::stackConsumption(Context &ctx) const {
  if (mIfCode != 0) {
    if (mIfCode->stackConsumption(ctx) != 0) {
      throw std::runtime_error("\"if/else\" statement \"if\" body must leave stack globaly unchanged");
    }
  }
  if (mElseCode != 0) {
    if (mElseCode->stackConsumption(ctx) != 0) {
      throw std::runtime_error("\"if/else\" statement \"else\" body must leave stack globaly unchanged");
    }
  }
  return 0;
}

bool IfElse::evalCondition(Stack &stack, Context &ctx) const {
  if (mCond == 0) {
    throw std::runtime_error("Missing condition for \"if/else\" statement");
  }
  int sz = stack.size();
  mCond->call(stack, ctx);
  if (stack.size() - sz != 1) {
    throw std::runtime_error("Detected stack corruption while evaluating \"if/else\" condition");
  }
  return stack.popBoolean();
}

int IfElse::eval(Stack &stack, Context &ctx) {
  if (evalCondition(stack, ctx)) {
    if (mIfCode) {
      Context ictx(&ctx);
      return mIfCode->call(stack, ictx);
    }
  } else {
    if (mElseCode) {
      Context ictx(&ctx);
      return mElseCode->call(stack, ictx);
    }
  }
  return EVAL_NEXT;
}

void IfElse::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "If";
  if (mCond) {
    os << std::endl;
    mCond->toStream(os, heading+"  ");
  }
  os << std::endl << heading << "Then";
  if (mIfCode) {
    os << std::endl;
    mIfCode->toStream(os, heading+"  ");
  }
  os << std::endl << heading << "Else";
  if (mElseCode) {
    os << std::endl;
    mElseCode->toStream(os, heading+"  ");
  }
}

// ---

While::While(Block *cond, Block *body)
  : Instruction(), mCond(cond), mBody(body) {
}

While::~While() {
  if (mCond) {
    mCond->decRef();
    mCond = 0;
  }
  if (mBody) {
    mBody->decRef();
    mBody = 0;
  }
}

Instruction* While::clone() const {
  return new While((Block*)(mCond ? mCond->clone() : 0),
                   (Block*)(mBody ? mBody->clone() : 0));
}

int While::stackConsumption(Context &ctx) const {
  if (mBody != 0) {
    if (mBody->stackConsumption(ctx) != 0) {
      throw std::runtime_error("\"while\" statement body must leave stack globaly unchanged");
    }
  }
  return 0;
}

bool While::evalCondition(Stack &stack, Context &ctx) const {
  if (mCond == 0) {
    throw std::runtime_error("Missing condition for \"while\" statement");
  }
  int sz = stack.size();
  mCond->call(stack, ctx);
  if (stack.size() - sz != 1) {
    throw std::runtime_error("Detected stack corruption while evaluating \"while\" condition");
  }
  return stack.popBoolean();
}

int While::eval(Stack &stack, Context &ctx) {
  int rv = EVAL_NEXT;
  Context wctx(&ctx);
  while (evalCondition(stack, ctx)) {
    if (mBody) {
      rv = mBody->call(stack, wctx);
      if (rv == EVAL_BREAK || rv == EVAL_RETURN) {
        break;
      }
      // if eval next of continue... proceed to next
    }
  }
  if (rv != EVAL_RETURN) {
    rv = EVAL_NEXT;
  }
  return rv;
}

void While::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "While ";
  if (mCond) {
    os << std::endl;
    mCond->toStream(os, heading+"  ");
  }
  os << std::endl << heading << "Do";
  if (mBody) {
    os << std::endl;
    mBody->toStream(os, heading+"  ");
  }
}

// ---

Break::Break()
  : Instruction() {
}

Break::~Break() {
}

Instruction* Break::clone() const {
  return new Break();
}

int Break::stackConsumption(Context &) const {
  return 0;
}

int Break::eval(Stack &, Context &) {
  return EVAL_BREAK;
}

void Break::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Break";
}

// ---

Return::Return()
  : Instruction() {
}

Return::~Return() {
}

Instruction* Return::clone() const {
  return new Return();
}

int Return::stackConsumption(Context &) const {
  return 0;
}

int Return::eval(Stack &, Context &) {
  return EVAL_RETURN;
}

void Return::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Return";
}

// ---

Continue::Continue()
  : Instruction() {
}

Continue::~Continue() {
}

Instruction* Continue::clone() const {
  return new Return();
}

int Continue::stackConsumption(Context &) const {
  return 0;
}

int Continue::eval(Stack &, Context &) {
  return EVAL_CONTINUE;
}

void Continue::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Continue";
}

// ---

CodeSegment::CodeSegment() {
}

CodeSegment::CodeSegment(const CodeSegment &rhs)
  : std::vector<Instruction*>() {
  for (size_t i=0; i<rhs.size(); ++i) {
    push_back(rhs[i]->clone());
  }
}

CodeSegment::~CodeSegment() {
  cleanup();
}

CodeSegment& CodeSegment::operator=(const CodeSegment &rhs) {
  if (this != &rhs) {
    cleanup();
    for (size_t i=0; i<rhs.size(); ++i) {
      push_back(rhs[i]->clone());
    }
  }
  return *this;
}

void CodeSegment::cleanup() {
  for (size_t i=0; i<size(); ++i) {
    delete (*this)[i];
  }
  clear();
}

int CodeSegment::stackConsumption(Context &ctx) const {
  int rv = 0;
  for (size_t i=0; i<size(); ++i) {
    rv += (*this)[i]->stackConsumption(ctx);
  }
  return rv;
}

int CodeSegment::eval(Stack &stack, Context &ctx) {
  int rv = EVAL_NEXT;
  for (size_t i=0; i<size(); ++i) {
    rv = (*this)[i]->eval(stack, ctx);
    if (rv != EVAL_NEXT) {
      return rv;
    }
  }
  return rv;
}

void CodeSegment::toStream(std::ostream &os, const std::string &heading) const {
  if (size() > 0) {
    for (size_t i=0; i<size()-1; ++i) {
      (*this)[i]->toStream(os, heading);
      os << std::endl;
    }
    (*this)[size()-1]->toStream(os, heading);
  }
}

std::ostream& operator<<(std::ostream &os, const CodeSegment &cs) {
  cs.toStream(os);
  return os;
}


