// krat_exp_expand.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HXX

# include <list>
# include <map>

# include <vaucanson/algorithms/krat_exp_expand.hh>

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>

namespace vcsn
{

  namespace algebra {

    // This is a trait to get more easily used types.
    template <typename S, typename T>
    struct pseudo_exp_list
    {
      typedef Element<S, T>				exp_t;
      typedef std::list<exp_t>				exp_list_t;
      typedef typename exp_t::semiring_elt_t		semiring_elt_t;
      typedef std::map<exp_list_t, semiring_elt_t>	ret_t;
    };

    // The Expander class. It break up the expression to build a map
    // and then rebuild it.
    template <class Series, class T, class Dispatch>
    struct KRatExpExpander : algebra::KRatExpMatcher<
      KRatExpExpander<Series, T, Dispatch>,
      T,
      typename pseudo_exp_list<Series, T>::ret_t,
      Dispatch
      >
    {
    public:
      typedef pseudo_exp_list<Series, T>			trait;
      typedef typename trait::exp_t				exp_t;
      typedef typename trait::ret_t				return_type;
      typedef typename trait::exp_list_t			exp_list_t;
      typedef KRatExpExpander<Series, T, Dispatch>		self_t;
      typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
      typedef typename semiring_elt_t::value_t			semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t		monoid_elt_t;
      typedef typename monoid_elt_t::set_t			monoid_t;
      typedef typename monoid_t::alphabet_t			alphabet_t;
      typedef typename alphabet_t::letter_t			letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpExpander(const exp_t& exp) :
	exp_(exp)
      {}

      // Some useful internal functions.
    private:
      // Convert the return_type into a rational expression.
      exp_t convert(const return_type& l)
      {
	typedef typename return_type::const_iterator	iterator;
	typedef typename exp_list_t::const_iterator	sub_iterator;

	exp_t result = exp_.structure().zero(SELECT(T));

	for (iterator i = l.begin(); i != l.end(); ++i)
	{
	  exp_list_t	l = i->first;
	  exp_t		e = l.front();
	  for (sub_iterator j = ++l.begin(); j != l.end(); ++j)
	    e *= *j;
	  result += i->second * e;
	}

	return result;
      }

      // Convert a standard expression into the corresponding breaked one.
      return_type convert(const exp_t& e)
      {
	exp_list_t	exp_list;
	exp_list.push_front(e);

	return_type	result;
	result[exp_list] =
	  exp_.structure().semiring().identity(SELECT(semiring_elt_value_t));

	return result;
      }

      // The union of two lists implemented by a map. If an element is in the
      // two lists then the weights are added.
      return_type list_union(const return_type& left,
			     const return_type& right)
      {
	typedef typename return_type::const_iterator	const_iterator;
	typedef typename return_type::iterator		iterator;

	return_type	result(left);
	for (const_iterator i = right.begin(); i != right.end(); ++i)
	{
	  iterator j = result.find(i->first);

	  if (j != result.end())
	    j->second += i->second;
	  else
	    result.insert(*i);
	}

	return result;
      }

      // Compute the concatenation of two list, regarding to handled elements.
      exp_list_t list_concat(const exp_list_t& left, const exp_list_t& right)
      {
	typedef typename exp_list_t::const_iterator	const_iterator;

	typename T::n_const_t* left_node =
	  dynamic_cast<typename T::n_const_t*>(left.back().value().base());
	typename T::n_const_t* right_node =
	  dynamic_cast<typename T::n_const_t*>(right.front().value().base());

	std::list<exp_t>	result(left);

	if (left_node and right_node)
	{
	  result.back() = exp_t(exp_.structure(),
				left_node->value_ + right_node->value_);
	  for (const_iterator i = ++right.begin(); i != right.end(); ++i)
	    result.push_back(*i);
	}
	else
	  for (const_iterator i = right.begin(); i != right.end(); ++i)
	    result.push_back(*i);
	return result;
      }

      // Public functions.
    public:
      // This function convert the result the original form.
      exp_t get()
      {
	return_type l = match(exp_.value());
	return convert(l);
      }

      // Match functions.
      MATCH__(Product, lhs, rhs)
      {
	typedef typename return_type::iterator		iterator;

	return_type llist = match(lhs);
	return_type rlist = match(rhs);
	return_type result;

	for (iterator i = llist.begin(); i != llist.end(); ++i)
	  for (iterator j = rlist.begin(); j != rlist.end(); ++j)
	    result[list_concat(i->first, j->first)] = i->second * j->second;
	return result;
      }
      END

      MATCH__(Sum, lhs, rhs)
      {
	return list_union(match(lhs), match(rhs));
      }
      END

      MATCH_(Star, e)
      {
	return_type l = match(e);
	return convert(convert(l).star());
      }
      END

      MATCH__(LeftWeight, w, e)
      {
	typedef typename return_type::iterator		iterator;

	return_type	l = match(e);
	return_type	result;

	for (iterator i = l.begin(); i != l.end(); ++i)
	  result[i->first] = semiring_elt_t(w) * i->second;
	return result;
      }
      END

      MATCH__(RightWeight, e, w)
      {
	typedef typename return_type::iterator		iterator;

	return_type	l = match(e);
	return_type	result;

	for (iterator i = l.begin(); i != l.end(); ++i)
	  result[i->first] = i->second * semiring_elt_t(w);
	return result;
      }
      END

      MATCH_(Constant, m)
      {
	return convert(exp_t(exp_.structure(), m));
      }
      END

      MATCH(Zero)
      {
	return convert(exp_.structure().zero(SELECT(T)));
      }
      END

      MATCH(One)
      {
	return convert(exp_.structure().identity(SELECT(T)));
      }
      END

    private:
	Element<Series, T>	exp_;
    };

    template <class S, class E>
    E do_expand(const algebra::SeriesBase<S>&, const E& exp)
    {
      typedef typename E::value_t	T;

      KRatExpExpander< S, T, algebra::DispatchFunction<T> >	matcher(exp);
      return matcher.get();
    }

    template <class Series, class T>
    Element<Series, T>
    expand(const Element<Series, T>& exp)
    {
      return do_expand(exp.structure(), exp);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_EXPAND_HXX
