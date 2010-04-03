#include "instruction.h"
#include "exception.h"
#include <sstream>

unsigned long gNumInstructions = 0;

Instruction::Instruction(const Location &loc) : mLocation(loc) {
  ++gNumInstructions;
}

Instruction::~Instruction() {
  --gNumInstructions;
#ifdef _DEBUG
  if (gNumInstructions == 0) {
    std::cout << "### All instructions deleted" << std::endl;
  }
#endif
}

// ---

Push::Push(const Location &loc, Object *o)
  : Instruction(loc), mValue(o) {
}

Push::Push(const Location &loc, bool v)
  : Instruction(loc), mValue(new Boolean(v)) {
}

Push::Push(const Location &loc, long v)
  : Instruction(loc), mValue(new Integer(v)) {
}

Push::Push(const Location &loc, double v)
  : Instruction(loc), mValue(new Double(v)) {
}

Push::Push(const Location &loc, const char *v)
  : Instruction(loc), mValue(new String(v)) {
}

Push::Push(const Location &loc, const std::string &v)
  : Instruction(loc), mValue(new String(v)) {
}

Push::~Push() {
  mValue->decRef();
}

Instruction* Push::clone() const {
  return new Push(getLocation(), mValue->clone());
}

int Push::eval(Stack *stack, Context *ctx) {
  // need an additonal incRef here or when decRef is called on the popped value from the stack
  // (as it should always be the case) we end up deleting the object.
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Push (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  mValue->incRef();
  if (!stack->push(mValue)) {
    std::ostringstream oss;
    oss << stack->getError() << " (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
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

Get::Get(const Location &loc, const std::string &name)
  : Instruction(loc), mName(name) {
}

Get::~Get() {
}

Instruction* Get::clone() const {
  return new Get(getLocation(), mName);
}

int Get::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Get \"" << mName << "\" (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  Object *o = ctx->getVar(mName);
  if (o == 0) {
    std::ostringstream oss;
    oss << "Undefined variable \"" << mName << "\" in context. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  stack->push(o);
  // Do not decRef, objects on stack must have at least double reference
  // not to be destroyed when popped
  //o->decRef();
  return EVAL_NEXT;
}

void Get::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Get \"" << mName << "\"";
}

// ---

Set::Set(const Location &loc, const std::string &name)
  : Instruction(loc), mName(name) {
}

Set::~Set() {
}

Instruction* Set::clone() const {
  return new Set(getLocation(), mName);
}

int Set::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Set \"" << mName << "\" (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  Object *o = stack->pop();
  ctx->setVar(mName, o);
  o->decRef();
  return EVAL_NEXT;
}

void Set::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Set \"" << mName << "\"";
}

// ---

DefFunc::DefFunc(const Location &loc, const std::string &name, Block *body)
  : Instruction(loc), mFnName(name), mBody(body) {
}
  
DefFunc::~DefFunc() {
  if (mBody) {
    mBody->decRef();
    mBody = 0;
  }
}

Instruction* DefFunc::clone() const {
  return new DefFunc(getLocation(), mFnName, (mBody ? (Block*) mBody->clone() : 0));
}

int DefFunc::eval(Stack *, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "DefFunc \"" << mFnName << "\" (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  Block *funcBody = (Block*) mBody->clone();
  funcBody->setContext(ctx);
  ctx->setVar(mFnName, funcBody);
  funcBody->decRef(); /* leave context the only owner */
  return EVAL_NEXT;
}

void DefFunc::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "DefFunc \"" << mFnName << "\"";
  if (mBody) {
    os << std::endl;
    mBody->toStream(os, heading+"  ");
  }
}

// ---

Call::Call(const Location &loc, const std::string &name)
  : Instruction(loc), mFnName(name) {
}

Call::~Call() {
}

Instruction* Call::clone() const {
  return new Call(getLocation(), mFnName);
}

int Call::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Call \"" << mFnName << "\" (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  Callable *o = (Callable*) ctx->getCallable(mFnName);
  if (o == NULL) {
    std::ostringstream oss;
    oss << "Undefined function \"" << mFnName << "\" in context. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  
  //return o->call(stack, ctx);
  CallStack *cs = ctx->getCallStack();
  
  if (cs) {
    cs->push_back(CallInfo(getLocation(), mFnName));
  }
  
  Context *dctx = o->getContext();
  Context *fctx = new Context(dctx);
  
  bool failed = false;
  o->call(stack, fctx, failed);
  
  fctx->decRef();
  dctx->decRef();
  
  if (failed) {
    throw Exception(o->getError(), cs);
  }
  
  o->decRef();
  
  if (cs) {
    cs->pop_back();
  }
  
  return EVAL_NEXT;
}

void Call::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Call \"" << mFnName << "\"";
}

// ---

If::If(const Location &loc, Block *cond, Block *code)
  : Instruction(loc), mCond(cond), mCode(code) {
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
  return new If(getLocation(), (mCond ? (Block*)mCond->clone() : 0), (mCode ? (Block*)mCode->clone() : 0));
}

bool If::evalCondition(Stack *stack, Context *ctx) const {
  if (mCond == 0) {
    std::ostringstream oss;
    oss << "Missing condition for \"if\" statement. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  int sz = stack->size();
  bool failed = false;
  mCond->call(stack, ctx, failed);
  if (failed) {
    throw Exception(mCond->getError(), ctx->getCallStack());
  }
  if (stack->size() - sz != 1) {
    std::ostringstream oss;
    oss << "Detected stack corruption while evaluating \"if\" condition. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  bool rv = stack->popBoolean(failed);
  if (failed) {
    throw Exception(stack->getError(), ctx->getCallStack());
  }
  return rv;
}

int If::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "If (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  if (evalCondition(stack, ctx)) {
    if (mCode) {
      Context *ictx = new Context(ctx);
      bool failed = false;
      int rv = mCode->call(stack, ctx, failed);
      ictx->decRef();
      if (failed) {
        std::ostringstream oss;
        oss << mCode->getError() << " (In " << getLocation().toString() << ")";
        throw Exception(oss.str(), ctx->getCallStack());
      }
      return rv;
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

IfElse::IfElse(const Location &loc, Block *cond, Block *ifCode, Block *elseCode)
  : Instruction(loc), mCond(cond), mIfCode(ifCode), mElseCode(elseCode) {
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
  return new IfElse(getLocation(),
                    (mCond ? (Block*)mCond->clone() : 0),
                    (mIfCode ? (Block*)mIfCode->clone() : 0),
                    (mElseCode ? (Block*)mElseCode->clone() : 0));
}

bool IfElse::evalCondition(Stack *stack, Context *ctx) const {
  if (mCond == 0) {
    std::ostringstream oss;
    oss << "Missing condition for \"if/else\" statement. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  int sz = stack->size();
  bool failed = false;
  mCond->call(stack, ctx, failed);
  if (failed) {
    throw Exception(mCond->getError(), ctx->getCallStack());
  }
  if (stack->size() - sz != 1) {
    std::ostringstream oss;
    oss << "Detected stack corruption while evaluating \"if/else\" condition. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  bool rv = stack->popBoolean(failed);
  if (failed) {
    throw Exception(stack->getError(), ctx->getCallStack());
  }
  return rv;
}

int IfElse::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "If/Else (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  if (evalCondition(stack, ctx)) {
    if (mIfCode) {
      Context *ictx = new Context(ctx);
      bool failed = false;
      int rv = mIfCode->call(stack, ictx, failed);
      ictx->decRef();
      if (failed) {
        std::ostringstream oss;
        oss << mIfCode->getError() << " (In " << getLocation().toString() << ")";
        throw Exception(oss.str(), ctx->getCallStack());
      }
      return rv;
    }
  } else {
    if (mElseCode) {
      Context *ictx = new Context(ctx);
      bool failed = false;
      int rv = mElseCode->call(stack, ictx, failed);
      ictx->decRef();
      if (failed) {
        std::ostringstream oss;
        oss << mElseCode->getError() << " (In " << getLocation().toString() << ")";
        throw Exception(oss.str(), ctx->getCallStack());
      }
      return rv;
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

While::While(const Location &loc, Block *cond, Block *body)
  : Instruction(loc), mCond(cond), mBody(body) {
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
  return new While(getLocation(),
                   (Block*)(mCond ? mCond->clone() : 0),
                   (Block*)(mBody ? mBody->clone() : 0));
}

bool While::evalCondition(Stack *stack, Context *ctx) const {
  if (mCond == 0) {
    std::ostringstream oss;
    oss << "Missing condition for \"while\" statement. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  int sz = stack->size();
  bool failed = false;
  mCond->call(stack, ctx, failed);
  if (failed) {
    throw Exception(mCond->getError(), ctx->getCallStack());
  }
  if (stack->size() - sz != 1) {
    std::ostringstream oss;
    oss << "Detected stack corruption while evaluating \"while\" condition. (In " << getLocation().toString() << ")";
    throw Exception(oss.str(), ctx->getCallStack());
  }
  bool rv = stack->popBoolean(failed);
  if (failed) {
    throw Exception(stack->getError(), ctx->getCallStack());
  }
  return rv;
}

int While::eval(Stack *stack, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "While (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  int rv = EVAL_NEXT;
  Context *wctx = new Context(ctx);
  while (evalCondition(stack, ctx)) {
    if (mBody) {
      bool failed = false;
      rv = mBody->call(stack, wctx, failed);
      if (failed) {
        wctx->decRef();
        std::ostringstream oss;
        oss << mBody->getError() << " (In " << getLocation().toString() << ")";
        throw Exception(oss.str(), ctx->getCallStack());
      }
      if (rv == EVAL_BREAK || rv == EVAL_RETURN) {
        break;
      }
      // if eval next of continue... proceed to next
    }
  }
  wctx->decRef();
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

Break::Break(const Location &loc)
  : Instruction(loc) {
}

Break::~Break() {
}

Instruction* Break::clone() const {
  return new Break(getLocation());
}

int Break::eval(Stack *, Context *ctx) {

#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Break (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  return EVAL_BREAK;
}

void Break::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Break";
}

// ---

Return::Return(const Location &loc)
  : Instruction(loc) {
}

Return::~Return() {
}

Instruction* Return::clone() const {
  return new Return(getLocation());
}

int Return::eval(Stack *, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Return (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
  return EVAL_RETURN;
}

void Return::toStream(std::ostream &os, const std::string &heading) const {
  os << heading << "Return";
}

// ---

Continue::Continue(const Location &loc)
  : Instruction(loc) {
}

Continue::~Continue() {
}

Instruction* Continue::clone() const {
  return new Return(getLocation());
}

int Continue::eval(Stack *, Context *ctx) {
  
#if defined(_DEBUG) and defined(_DEBUG_VERBOSE)
  std::string indent = "";
  int depth = ctx->getDepth();
  for (int i=0; i<depth; ++i) {
    indent += "  ";
  }
  std::cerr << "### " << indent << "Continue (in context 0x" << std::hex << (void*)ctx << std::dec << ")" << std::endl;
#endif
  
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

int CodeSegment::eval(Stack *stack, Context *ctx) {
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


