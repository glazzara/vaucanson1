// contract.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_MISC_CONTRACT_HH
# define VCSN_MISC_CONTRACT_HH

/** @addtogroup utility *//** @{ */
/** @addtogroup contract Contract checking for Vaucansn *//** @{ */

/**
 * In Vaucanson, several types of contracts can be placed in the
 * library code.
 *
 * <h1>Assertions</h1>
 *
 * Assertions are a weak kind of contract, which states that a
 * specified property must hold.
 * 
 * A failed assertion should always mean that an internal
 * inconsistency has been detected, caused by a software (or hardware)
 * bug.
 *
 * <h1>Preconditions</h1>
 *
 * Preconditions ensure that the prerequisites for using a function or
 * instanciating a template are fulfilled.
 *
 * Breach of a precondition should prevent the library user from using
 * a feature, either generating a type error for forbidden template
 * instanciations or run-type exception at function entry.
 *
 * <h1>Postconditions</h1>
 *
 * Postconditions ensure that the result of a computation exhibit the
 * specified properties.
 *
 * Breach of a precondition should show that an algorithm is false.
 *
 * <h1>Call to pure abstract services</h1>
 *
 * Some services are purely abstract and should not be called
 * directly. In most cases this kind of information is expressed
 * through C++ typing.
 *
 * <h1>Warnings</h1>
 *
 * In addition to contracts, the library is equiped with mechanisms
 * intended to inform the user of misbehaviors, undocumented
 * properties, deprecated features and so on.
 *
 * <h2>Deprecated features</h2>
 *
 * Deprecated features are features that have been superceded by
 * others, and intended to be removed at some point.
 *
 * <h2>Weak implementations</h2>
 *
 * Weak implementations are code pieces written to ensure that a
 * specified feature is provided, but was not tested for full
 * conformance.
 *
 * Weak implementations should work with most trivial cases but denote
 * a library weakness on which the developers will focus.
 *
 * <h2>Incomplete implementation</h2>
 *
 * Incomplete implementations are code pieces written to ensure that a
 * specified expressivity is provided, but without providing the
 * actual feature.
 */

#ifdef NDEBUG

#define static_assertion(Cond, Message) typedef void Message
#define static_error(Message) typedef void Message

#define assertion(Cond) static_cast<void>(0)
#define precondition(Cond) static_cast<void>(0)
#define postcondition(Cond) static_cast<void>(0)

#define pure_service_call(Service) static_cast<void>(0)

#define deprecation(Feature) static_cast<void>(0)
#define weakness(Feature) static_cast<void>(0)
#define incompletion(Feature) static_cast<void>(0)

#define warning(Message) static_cast<void>(0)

#else // !NDEBUG

#include <vaucanson/config/system.hh>
#include <vaucanson/misc/static.hh>

#include <iostream>
#include <string>
#ifdef EXCEPTION_TRAPS
#include <sstream>
#include <stdexcept>
#else
#include <cstdlib>
#endif

namespace utility {
  namespace contract {

    static inline
    void trap(const char *file, int line,
	      const char *location,
	      const std::string& message)
    {
#ifdef EXCEPTION_TRAPS
      std::ostringstream os;
      os << file << ':' << line << ':' 
	 << (location ? location : "")
	 << (location ? ": " : " ")
	 << message;
      throw std::logic_error(os.str());
#else
      std::cerr << file << ':' << line << ':'
		<< (location ? location : "")
		<< std::endl
		<< '\t' << message
		<< std::endl;
      abort();
#endif
    }

    template<typename T>
    struct fail;

  }
}

#define __trap(Message, Cond) \
   utility::contract::trap(__FILE__, __LINE__, PRETTY_FUNCTION(), \
			     std::string(Message) + ": " #Cond)

#define assertion(Cond) static_cast<void>((Cond) ? static_cast<void>(0) : __trap("Assertion failed", Cond))
#define precondition(Cond) static_cast<void>((Cond) ? static_cast<void>(0) : __trap("Precondition failed", Cond))
#define postcondition(Cond) static_cast<void>((Cond) ? static_cast<void>(0) : __trap("Postcondition failed", Cond))

#define pure_service_call(Service) __trap("Pure absract service called", Service)

#define static_assertion(Cond, Message) \
  { utility::static_if<Cond, int, utility::contract::fail<void> >::t Message; Message = 0; }

#define static_error(Message) utility::contract::fail<Message> Message

#ifndef INTERNAL_CHECKS

#define deprecation(Feature) static_cast<void>(0)
#define weakness(Feature) static_cast<void>(0)
#define incompletion(Feature) static_cast<void>(0)

#define warning(Message) static_cast<void>(0)

#else

#ifdef STRICT
#define __inconsistency(Message1, Message2) __trap(Message1, Message2)
#else
#define __inconsistency(Message1, Message2) \
  (std::cerr << __FILE__ << ':' << __LINE__ << ": " \
   << Message1 << ": " << Message2 << std::endl)
#endif // STRICT

#define deprecation(Feature) __inconsistency("Deprecated feature", Feature)
#define weakness(Feature) __inconsistency("Weak feature", Feature)
#define incompletion(Feature) __inconsistency("Incomplete implementation", Feature)
#define warning(Message) __inconsistency("Warning", Message)

#endif // INTERNAL_CHECKS

#endif // NDEBUG

#endif // VCSN_MISC_CONTRACT_HH
