/*********************
 * <types/symbol.hh> *
 *********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TYPES_SYMBOL_HH
#define TYPES_SYMBOL_HH

#include <iostream>
#include <string>
#include <set>

namespace vcsn
{
  namespace vauc
  {
   
    class Symbol
    {
    public:
      Symbol(const std::string &s);

      Symbol(const char* str);

      Symbol(const Symbol& other);

      Symbol& operator=(const Symbol& other);
      const std::string& name() const;
      
    protected:
      const std::string* name_;
    };


  }
}

#include <types/symbol.hxx>

#endif
