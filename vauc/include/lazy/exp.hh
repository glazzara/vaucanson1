/*****************
 * <lazy/exp.hh> *
 *****************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_EXP_HH
#define LAZY_EXP_HH

#include <lazy/exp_base.hh>
#include <lazy/visitor_base.hh>

namespace vcsn
{
  namespace vauc
  {

    class LazyExp
    {
    public:
      LazyExp(const lazy::Exp<VisitorBase>& e);
      LazyExp(lazy::Exp<VisitorBase>* e);
      LazyExp();
      LazyExp(const LazyExp& other);

      LazyExp& operator=(const LazyExp& other);

      bool bound() const;

      lazy::Exp<VisitorBase>& exp() const;

      ~LazyExp();

      void attach(lazy::Exp<VisitorBase>* e);

    protected:
      lazy::Exp<VisitorBase>* exp_;

    };

  }

}

#include <lazy/exp.hxx>

#endif
