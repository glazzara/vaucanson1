// char_traits.hh: this file is part of the Vaucanson project.
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
//

/** @addtogroup utility *//** @{ */
/**
 * @file char_traits.hh
 *
 * @brief Generic char_traits declarations.
 *
 * This  file  contains  the  utility::char_traits  declaration.  This
 * structure should allow  a programmer to specialize std::char_traits
 * for some types with little efforts.
 *
 * For example, you may write (while in the std namespace):
 *
 * template <>
 * struct char_traits<foo> : public utility::char_traits<foo> { };
 *
 * To have a  generic specialization of char_traits for  foo.  You may
 * also  use  this  kind  of  derivation and  redifine  a  few  member
 * functions  to have  a more  effective implementation  based  on the
 * generic version.
 *
 * If you are looking for allready written specializations, you should
 * look at vaucanson/misc/special_char_traits.hh.
 *
 * @authors Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see utility::char_traits, vaucanson/misc/special_char_traits.hh
 */
/** @} */

#ifndef VCSN_MISC_CHAR_TRAITS_HH
# define VCSN_MISC_CHAR_TRAITS_HH

# include <string>

namespace utility
{

  /** @addtogroup utility */ /** @{ */

  /**
   * Generic and under-efficient int_type implementation for char_traits.
   *
   * This class  provides a generic implementation  of int_type inside
   * char_traits.   generic_int_type<T>  should  provide  a  type  big
   * enough to hold all values of T plus a value dedicated to EOF.
   */
  template <class CharT>
  struct generic_int_type
  {
    typedef CharT char_type;

    generic_int_type();
    generic_int_type(const char_type&);

    operator CharT () const;

    bool operator == (const generic_int_type<CharT>&) const;
    bool eof() const;
  protected:
    char_type val_;
    bool eof_;
  };

  /**
   * Generic char_traits.
   *
   * Provides generic char_traits  to specialize std::char_traits with
   * minimal   efforts.   So   it    should   be   possible   to   use
   * std::basic_string with almost any type.
   */
  template <typename CharT>
  struct char_traits
  {
    typedef CharT			char_type;
    typedef generic_int_type<char_type>	int_type;
    typedef std::streamoff		off_type;
    typedef std::streampos		pos_type;
    typedef mbstate_t			state_type;

    static void			assign(char_type&, const char_type&);
    static bool			eq(const char_type&, const char_type&);
    static bool			lt(const char_type&, const char_type&);
    static int			compare(const char_type*,
					const char_type*,
					size_t);
    static size_t		length(const char_type*);
    static const char_type*	find(const char_type*,
				     size_t,
				     const char_type&);
    static char_type*		move(char_type*, const char_type*, size_t);
    static char_type*		copy(char_type*, const char_type*, size_t);
    static char_type*		assign(char_type*, size_t, char_type);
    static int_type		not_eof(const int_type&);
    static char_type		to_char_type(const int_type&);
    static int_type		to_int_type(const char_type&);
    static bool			eq_int_type(const int_type&, const int_type&);
    static int_type		eof();
  };

  /** @} */
} // end of namespace utility

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/char_traits.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_MISC_CHAR_TRAITS_HH
