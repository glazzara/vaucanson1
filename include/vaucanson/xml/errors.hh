// errors.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_XML_ERRORS_HH
# define VCSN_XML_ERRORS_HH

/** @addtogroup xml *//** @{ */

/**
 * @file errors.hh
 *
 * Error treatment for XML tools.
 *
 * @author Valentin David <valentin@lrde.epita.fr>
 */

# ifndef FAIL
#  define FAIL WITH_EXIT
# endif

/** @} */

/// Errors make exits, use with @c #define @c FAIL @c WITH_EXIT
# define WITH_EXIT(X) { warning( X ); exit(-1); }

/// Errors make throws, use with @c #define @c FAIL @c WITH_THROW
# define WITH_THROW(X) throw(LoaderException( X ))

# include <string>

namespace vcsn
{

  namespace xml
  {

    /** @addtogroup xml *//** @{ */

    /// Exception thrown by XML read operation.
    class LoaderException
    {
    public:
      LoaderException(const std::string& msg) : _msg(msg) { }

      /// Get the error message.
      std::string get_msg() const
      {
	return _msg;
      }

    private:
      std::string _msg;
    };

  } // End of namespace xml.

} // End of namespace vcsn.

#endif // ! VCSN_XML_ERRORS_HH
