// partial_rat_exp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HH
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HH

/**
 * @file partial_rat_exp.hh
 * @author Loic Fosse <loic@lrde.epita.fr>
 * @date   Fri Jul  4 11:53:07 CEST 2003
 * 
 * @brief The @c PartialExp type. (undocumented)
 *
 * This file discribe the PartialExp type and operations on it.
 * @c PartialExp is a way to describe derivatives with a list of pointer.
 * It is usefull in algorithms like @c derivatives_automaton.
 */

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <list>

namespace vcsn
{
  /*-----------------.
  | PartialExp class |
  `-----------------*/

  // An implementation of Derivates represented by list of pointers.
  template <typename Series, typename T>
  struct PartialExp
  {
    // Common types
    typedef Element<Series, T>			exp_t;
    typedef Series				series_t;
    typedef T					series_impl_t;
    typedef typename T::node_t			value_t;
    typedef typename exp_t::semiring_elt_t	semiring_elt_t;

    /* 
     * A std::list is used because pop_front is needed,
     * and we must be able to modify an element of the list.
     */
    typedef std::list<const value_t*>		ptr_list_t;
    typedef typename ptr_list_t::const_iterator	const_iterator;
    typedef typename ptr_list_t::iterator	iterator;

    // Constructors
    // Be carefull: the exp must be realtime !
    PartialExp(const exp_t &e);
    PartialExp(const PartialExp &other);

    // Be carefull: this operator multiply the two weight, but
    // it is w * weight_ that is computed.
    PartialExp& operator^=(semiring_elt_t w);
    PartialExp& insert(const value_t *v);
    
    // Accessors
    semiring_elt_t&		weight();
    const semiring_elt_t&	weight() const;
    ptr_list_t&		ptr_list();
    const ptr_list_t&	ptr_list() const;

    // Accessor for the rat_exp and usefull methods
    const exp_t&	exp() const;
    const Series&	exp_structure() const;
    const T&		exp_value() const;

    // Iterator functions
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

  protected:
    const exp_t*	rat_exp_;
    semiring_elt_t	weight_;
    ptr_list_t		ptr_list_;
  };

  /*---------------------.
  | PartialExp functions |
  `---------------------*/

  template <typename S, typename T>
  std::ostream& operator<< (std::ostream& o, PartialExp<S, T> e);

  // Be carefull: the exp must be realtime !
  template <typename S, typename T>
  PartialExp<S, T> prat_exp_convert(const Element<S, T>& exp);
  
  template <typename S, typename T>
  bool operator< (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

  template <typename S, typename T>
  bool operator== (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/internal/partial_rat_exp.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HH
