/**********************
 * <types/symbol.hxx> *
 **********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TYPES_SYMBOL_HXX
#define TYPES_SYMBOL_HXX

#include <types/symbol.hh>


namespace vcsn
{
  namespace vauc
  {
    std::set<std::string>& persistant_strings();
 
    inline Symbol::Symbol(const std::string &s)
    {
      std::pair<const std::set<std::string>::iterator, bool>
	i = persistant_strings().insert(s);
      name_ = &(*i.first); // no, this *really* does not simplify
    }

    inline Symbol::Symbol(const char* str)
    {
      std::pair<const std::set<std::string>::iterator, bool>
	i = persistant_strings().insert(std::string(str));
      name_ = &(*i.first);
    }

    inline Symbol::Symbol(const Symbol& other) 
      : name_(other.name_)
    {}

    inline Symbol& Symbol::operator=(const Symbol& other)
    { name_ = other.name_; return *this; }

    inline const std::string& Symbol::name() const
    { return *name_; }



    inline bool operator==(const Symbol& lhs, const Symbol& rhs)
    { return &(lhs.name()) == &(rhs.name()); }

    inline bool operator!=(const Symbol& lhs, const Symbol& rhs)
    { return &(lhs.name()) != &(rhs.name()); }

    inline bool operator<(const Symbol& lhs, const Symbol& rhs)
    { return lhs.name() < rhs.name(); }

    inline bool operator>(const Symbol& lhs, const Symbol& rhs)
    { return lhs.name() > rhs.name(); }

    inline bool operator<=(const Symbol& lhs, const Symbol& rhs)
    { return lhs.name() <= rhs.name(); }

    inline bool operator>=(const Symbol& lhs, const Symbol& rhs)
    { return lhs.name() >= rhs.name(); }

    inline std::ostream& operator<<(std::ostream& out, const Symbol& rhs)
    { return out << (rhs.name()); }

  }
}

#endif
