// contract.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_MISC_CONTRACT_HH
# define VCSN_MISC_CONTRACT_HH

# ifdef NDEBUG
#  define assertion(expr)         ((void) 0)
#  define invariant(expr)         ((void) 0)
#  define precondition(expr)      ((void) 0)
#  define postcondition(expr)     ((void) 0)
# else 
#  define assertion(expr)         VCSNTestCondition(Assertion,expr)
#  define invariant(expr)         VCSNTestCondition(Invariant,expr)
#  define precondition(expr)      VCSNTestCondition(Precondition,expr)
#  define postcondition(expr)     VCSNTestCondition(Postcondition,expr)

# include <iostream>
# include <string>

namespace vcsn {
  namespace misc {

    inline 
    void
    failed_condition(const std::string& cond_type,
		     const std::string& cond_text, 
		     const std::string& filename, 
		     int line)
    {
      std::cerr << filename << ":" 
		<< line << ":"
		<< cond_type << ":  <<"
		<< cond_text << " >> is false."
		<< std::endl;
    }

  } // misc
} // vcsn

#  define VCSNTestCondition(condType,expr)	\
  if (!(expr))					\
    ::vcsn::misc::failed_condition(#condType,	\
                                    #expr,	\
				    __FILE__,	\
				    __LINE__ );
# endif // ! NDEBUG


#endif // ! OLENA_CORE_CONTRACT_HH
