#ifndef __symbol_h_
#define __symbol_h_

#include "hashmap.h"
#include <iostream>
#include <string>

class Symbol {
  public:
    Symbol();
    Symbol(size_t v);
    Symbol(const std::string &s);
    Symbol(const Symbol &rhs);
    ~Symbol();
    Symbol& operator=(const Symbol &rhs);
    bool valid() const;
    size_t id() const;
    friend bool operator<(const Symbol &s0, const Symbol &s1);
    friend std::ostream& operator<<(std::ostream &os, const Symbol &s);
  protected:
    size_t mID;
};

class SymbolTable {
  public:
    
    typedef HashMap<std::string, size_t> HashType;
    
  public:
    
    static SymbolTable& Instance();
    static const char* GetString(const Symbol &s);
    static Symbol GetSymbol(const std::string &name);
    
    ~SymbolTable();
    
  protected:
    
    SymbolTable();
    
    Symbol getSymbol(const std::string &name);
    const char* getString(const Symbol &s);
    
  protected:
    
    HashType mSyms;
    std::vector<std::string> mStrs;
};

// ---

inline Symbol::Symbol()
  : mID(size_t(-1)) {
}

inline Symbol::Symbol(size_t v)
  : mID(v) {
}

inline Symbol::Symbol(const std::string &s)
  : mID(size_t(-1)) {
  Symbol sym = SymbolTable::GetSymbol(s);
  mID = sym.mID;
}

inline Symbol::Symbol(const Symbol &rhs)
  : mID(rhs.mID) {
}

inline Symbol::~Symbol() {
}

inline Symbol& Symbol::operator=(const Symbol &rhs) {
  mID = rhs.mID;
  return *this;
}

inline bool Symbol::valid() const {
  return (mID != size_t(-1));
}

inline size_t Symbol::id() const {
  return mID;
}

inline bool operator<(const Symbol &s0, const Symbol &s1) {
  return (s0.mID < s1.mID);
}

inline std::ostream& operator<<(std::ostream &os, const Symbol &s) {
  const char *cs = SymbolTable::GetString(s);
  os << (cs == 0 ? "" : cs);
  return os;
}

#endif
