#include "symbol.h"

SymbolTable *gInstance = 0;

void SymbolTable::Clear() {
  if (gInstance) {
    delete gInstance;
    gInstance = 0;
  }
}

const char* SymbolTable::GetString(const Symbol &s) {
  if (!gInstance) {
    gInstance = new SymbolTable();
  }
  return gInstance->getString(s);
}

Symbol SymbolTable::GetSymbol(const std::string &name) {
  if (!gInstance) {
    gInstance = new SymbolTable();
  }
  return gInstance->getSymbol(name);
}

SymbolTable::SymbolTable() {
}

SymbolTable::~SymbolTable() {
  mSyms.clear();
  mStrs.clear();
}

Symbol SymbolTable::getSymbol(const std::string &name) {
#ifdef _SYMTBLH
  size_t sym;
  if (mSyms.getValue(name, sym)) {
    return Symbol(sym);
  } else {
    sym = mStrs.size();
    mSyms.insert(name, sym);
    mStrs.push_back(name);
    return Symbol(sym);
  }
#else
  HashType::iterator it = mSyms.find(name);
  if (it != mSyms.end()) {
    return Symbol(it->second);
  } else {
    size_t sym = mStrs.size();
    mSyms[name] = sym;
    mStrs.push_back(name);
    return Symbol(sym);
  }
#endif
}

const char* SymbolTable::getString(const Symbol &s) {
  if (s.valid() && s.id() < mStrs.size()) {
    return mStrs[s.id()].c_str();
  } else {
    return 0;
  }
}
