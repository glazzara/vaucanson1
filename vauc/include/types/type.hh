/*******************
 * <types/type.hh> *
 *******************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TYPES_TYPE_HH
#define TYPES_TYPE_HH

#include <string>

#include <triplet.hh>

namespace vcsn
{
  namespace vauc
  {

    typedef utility::triplet<
      std::string /* id == typeid().name() */,
      std::string /* name */,
      std::string /* description */
      > typeinfo_t;
          
  } // vauc
} // vcsn


#endif
