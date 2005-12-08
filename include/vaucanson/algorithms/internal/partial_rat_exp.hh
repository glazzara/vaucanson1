// partial_rat_exp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
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
 * It is usefull in algorithms like @c derived_term_automaton.
 */

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <list>

namespace vcsn
{
  /*---------------------.
  | Traits for iterators |
  `---------------------*/

  template <bool IsConst, typename T>
  struct reference_type
  { typedef T& ret; };

  template <typename T>
  struct reference_type<true, T>
  { typedef const T& ret; };

  template <bool IsConst, typename T>
  struct iterator_type
  { typedef typename T::iterator ret; };

  template <typename T>
  struct iterator_type<true, T>
  { typedef typename T::const_iterator ret; };

  /*-----------------.
  | PartialExp class |
  `-----------------*/

  // An implementation of Derivates represented by list of pointers.
  template <typename Series, typename T>
  struct PartialExp
  {
    // Common types
    typedef Element<Series, T>			exp_t;
    typedef Series				series_set_t;
    typedef T					series_set_elt_value_t;
    typedef typename T::node_t			node_t;
    typedef typename exp_t::semiring_elt_t	semiring_elt_t;

    /*
     * A std::list is used because pop_front is needed,
     * and we must be able to modify an element of the list.
     */
    typedef std::list<const node_t*>		node_list_t;
    typedef std::list<semiring_elt_t>		semiring_elt_list_t;

    // Constructors
    // Be carefull: the exp must be realtime !
    PartialExp(const exp_t &e);
    PartialExp(const exp_t &e, const semiring_elt_t& w);
    PartialExp(const PartialExp &other);

    // Insert a new node into the list, and add another weight "after".
    PartialExp&				insert(const node_t *v);

    // Accessors
    semiring_elt_list_t&		weights();
    const semiring_elt_list_t&		weights() const;
    node_list_t&			nodes();
    const node_list_t&			nodes() const;

    // Operators to change weights
    PartialExp&				operator<<=(const semiring_elt_t& w);
    PartialExp&				operator>>=(const semiring_elt_t& w);

    // Accessor for the rat_exp and usefull methods
    const exp_t&			exp() const;
    const Series&			exp_structure() const;
    const T&				exp_value() const;

  protected:
    // Protected attributes
    const exp_t*			rat_exp_;
    semiring_elt_list_t			semiring_elt_list_;
    node_list_t				node_list_;

  public:
    // internal class for iterator and const_iterator
    template <bool IsConst>
    struct internal_iterator
    {
    public:
      typedef typename
      reference_type<IsConst,semiring_elt_t>::ret	semiring_elt_ref_t;
      typedef typename
      reference_type<IsConst,const node_t*>::ret	node_ref_t;
      typedef typename
      iterator_type<IsConst,semiring_elt_list_t>::ret	semiring_elts_iterator_t;
      typedef typename
      iterator_type<IsConst,node_list_t>::ret		nodes_iterator_t;
    public:
      internal_iterator(const semiring_elts_iterator_t&,
			const nodes_iterator_t&);
      internal_iterator&	operator++();
      internal_iterator		operator++(int);
      bool			operator!=(const internal_iterator& other);
      bool			operator==(const internal_iterator& other);
      semiring_elt_ref_t	semiring_elt() const;
      node_ref_t		node() const;
      bool			on_node() const;
    protected:
      semiring_elts_iterator_t	semiring_elts_iterator_;
      nodes_iterator_t		nodes_iterator_;
      bool			on_node_;
    };

    // definitions of iterator and const_iterator
    typedef internal_iterator<false>	iterator;
    typedef internal_iterator<true>	const_iterator;

    // iterators functions
    iterator				begin();
    iterator				end();
    const_iterator			begin() const;
    const_iterator			end() const;
  };

  /*---------------------.
  | PartialExp functions |
  `---------------------*/

  template <typename S, typename T>
  std::ostream& operator<< (std::ostream& o, const PartialExp<S, T>& e);

  // Be carefull: the exp must be realtime !
  template <typename S, typename T>
  std::list<PartialExp<S, T> > prat_exp_convert(const std::list<Element<S, T> >& exp);

  template <typename S, typename T>
  PartialExp<S, T> prat_exp_convert(const Element<S, T>& exp);

  template <typename S, typename T>
  bool operator< (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

  template <typename S, typename T>
  bool operator== (const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

  template <typename S, typename T>
  bool unweighted_eq(const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

  template <typename S, typename T>
  bool unweighted_inf(const PartialExp<S, T>& e1, const PartialExp<S, T>& e2);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algorithms/internal/partial_rat_exp.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_HH
