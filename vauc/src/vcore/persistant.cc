/************************
 * symbol/persistant.cc *
 ************************/
// $Id$

/* this file is part of the Vaucanson project */

#include <types/symbol.hh>

namespace vcsn
{
  namespace vauc
  {
    
    static std::set<std::string> persistant_strings_instance;

    std::set<std::string>& persistant_strings()
    {
      return persistant_strings_instance;
    }
  }
}
