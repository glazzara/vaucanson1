// partial_rat_exp_derivation.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HXX
# define VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HXX

# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn {

  template <typename T>
  void list_fusion_here(std::list<T>& dst, const std::list<T>& src)
  {
    typedef typename std::list<T>::const_iterator	const_iterator;
    for (const_iterator i = src.begin(); i != src.end(); ++i)
      dst.push_back(*i);
  }

  template <typename S, typename T>
  void list_multiply_here_left(std::list<PartialExp<S, T> >& l,
			       const typename PartialExp<S, T>::semiring_elt_t& w)
  {
    typedef std::list<PartialExp<S, T> >	list_t;
    for (typename list_t::iterator i = l.begin(); i != l.end(); ++i)
      *i >>= w;
  }

  template <typename S, typename T>
  void list_multiply_here_right(std::list<PartialExp<S, T> >& l,
			       const typename PartialExp<S, T>::semiring_elt_t& w)
  {
    typedef std::list<PartialExp<S, T> >	list_t;
    for (typename list_t::iterator i = l.begin(); i != l.end(); ++i)
      *i <<= w;
  }

  template <typename S, typename T>
  void list_insert_here(std::list<PartialExp<S, T> >& l,
			const typename PartialExp<S,T>::node_t* elm)
  {
    typedef std::list<PartialExp<S, T> >	list_t;
    for (typename list_t::iterator i = l.begin(); i != l.end(); ++i)
      i->insert(elm);
  }

  /**
   * @brief  This class performs partial rational expression derivations.
   *
   * @bug FIXME: This class heavily lacks of documentation.
   * @bug FIXME: Make list be a unique container.
   */
  template <typename Series, typename T>
  class PRatExpDerivationVisitor :
    public rat::ConstNodeVisitor<typename T::monoid_elt_value_t,
  				 typename T::semiring_elt_value_t>
  {
  public:
    typedef Element<Series, T>				exp_t;
    typedef T						series_set_elt_value_t;
    typedef typename T::node_t				node_t;
    typedef typename std::list<PartialExp<Series, T> >	return_type;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
    typedef typename monoid_elt_t::set_t		monoid_t;
    typedef typename monoid_t::alphabet_t		alphabet_t;
    typedef typename alphabet_t::letter_t		letter_t;

  public:
    PRatExpDerivationVisitor(const exp_t&	exp,
			     const letter_t&	a) :
      undefined(false),
      exp_(exp),
      a_(a),
      father_(NULL)
    {}

    virtual
    ~PRatExpDerivationVisitor()
    {}

    void match(const node_t* node)
    {
      father_ = node;
      node->accept(*this);
    }

  private:
    Element<Series, T> series(const T& e)
    {
      return Element<Series, T>(exp_.structure(), e);
    }

  public:
    virtual void
    product(const node_t* lhs, const node_t* rhs)
    {
      std::pair<semiring_elt_t, bool> ret =
	constant_term(series(series_set_elt_value_t(lhs)));
      if (ret.second == false)
      {
	undefined = true;
	return ;
      }

      return_type tmp;
      if ( ret.first !=
	   exp_.structure().semiring().zero(SELECT(semiring_elt_value_t)))
      {
	match(rhs);
	list_multiply_here_left(result, ret.first);
	tmp = result;
      }

      match(lhs);
      list_insert_here(result, rhs);
      list_fusion_here(result, tmp);
    }

    virtual void
    sum(const node_t* lhs, const node_t* rhs)
    {
      match(rhs);
      return_type tmp = result;
      match(lhs);
      list_fusion_here(result, tmp);
    }

    virtual void
    star(const node_t* node)
    {
      assertion(father_ != NULL);
      const typename T::node_t* father = father_;

      std::pair<semiring_elt_t, bool> ret =
	constant_term(series(series_set_elt_value_t(node)));
      if ((ret.second == false) || (ret.first.starable() == false))
      {
	undefined = true;
	return;
      }

      match(node);
      list_insert_here(result, father);
      list_multiply_here_left(result, ret.first.star());
    }

    virtual void
    left_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      match(node);
      list_multiply_here_left(result, semiring_elt_t(w));
    }

    virtual void
    right_weight(const semiring_elt_value_t& w, const node_t* node)
    {
      match(node);
      list_multiply_here_right(result, semiring_elt_t(w));
    }

    virtual void
    constant(const monoid_elt_value_t& m)
    {
      result = return_type();
      if (m.length() != 1)
      {
	warning("PartialExp base is not realtime.");
	undefined = true;
	return;
      }
      if (m[0] == a_)
      	result.push_back(PartialExp<Series, T>(exp_));
    }

    virtual void
    zero()
    {
      result = return_type();
    }

    virtual void
    one()
    {
      result = return_type();
    }

  public:
    bool			undefined;
    return_type			result;

  private:
    const exp_t&		exp_;
    const letter_t&		a_;
    const typename T::node_t*	father_;
  };


/*****************************************************************************/
/***************************** User's functions ******************************/
/*****************************************************************************/

  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const Element<Series, T>& exp,
 	  	    Letter a)
  {
    PRatExpDerivationVisitor<Series, T> visitor(exp, a);
    visitor.match(exp.value().base());
    return std::make_pair(visitor.result, !visitor.undefined);
  }

  template <class Series, class T, class Letter>
  std::pair<std::list<PartialExp<Series, T> >, bool>
  prat_exp_derivate(const PartialExp<Series, T>& exp,
 	  	    Letter a)
  {
    typedef PartialExp<Series, T>			exp_t;
    typedef std::list<PartialExp<Series, T> >		exp_list_t;
    typedef std::pair<exp_list_t, bool>			return_type;
    typedef typename exp_t::const_iterator		const_iterator;
    typedef typename Element<Series, T>::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef T						series_set_elt_value_t;

    // Save the first weight, and go to the first expression
    const_iterator i = exp.begin();
    semiring_elt_t w = i.semiring_elt();
    i++;
    
    // Check if the exp is not empty
    if (i == exp.end())
      return std::make_pair(exp_list_t(), true);
    
    // Visit the first element of the exp
    PRatExpDerivationVisitor<Series, T> visitor(exp.exp(), a);
    const typename exp_t::node_t*	n = i.node();
    visitor.match(n);

    // Insert other pointers and values into the result
    for (i++; i != exp.end(); ++i)
      if (i.on_node())
	list_insert_here(visitor.result, i.node());
      else
	list_multiply_here_right(visitor.result, i.semiring_elt());

    // Calculate the constant term
    std::pair<semiring_elt_t, bool> cterm =
      constant_term(Element<Series, T>(exp.exp_structure(), series_set_elt_value_t(n)));
    if (cterm.second == false)
      return std::make_pair(exp_list_t(), false);

    // --------  If cterm != 0, look at the rest of the list  ---------------
    if (cterm.first !=
	exp.exp_structure().semiring().zero(SELECT(semiring_elt_value_t)) )
    {
      // Build an exp from the orignal, without the head
      exp_t new_exp(exp);
      new_exp.nodes().pop_front();
      new_exp.weights().pop_front();

      // Recall prat_exp_derivate on it
      return_type ret = prat_exp_derivate(new_exp, a);

      // Multiply by constant term
      list_multiply_here_left(ret.first, cterm.first);

      // Fusion results
      visitor.undefined = visitor.undefined || !ret.second;
      list_fusion_here(visitor.result, ret.first);
    }
    //------------------------------------------------------------------------

    // Multiply by the weight of exp
    list_multiply_here_left(visitor.result, w);

    // Return the final result
    return std::make_pair(visitor.result, !visitor.undefined);
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_INTERNAL_PARTIAL_RAT_EXP_DERIVATION_HXX
