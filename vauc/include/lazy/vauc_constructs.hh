/*****************************
 * <lazy/vauc_constructs.hh> *
 *****************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef LAZY_VAUC_CONSTRUCTS_HH
#define LAZY_VAUC_CONSTRUCTS_HH

#include <list>
#include <types/object.hh>
#include <lazy/exp_base.hh>

namespace vcsn
{
  namespace vauc
  {

    namespace lazy
    {

      struct lazy_call_k
      { static const size_t arity = 2; enum types { a_fun, a_args }; };

      template<typename Visitor>
      class LazyCall : public ExpImpl<Visitor, lazy_call_k> {};

      struct call_k
      { static const size_t arity = 2; enum types { a_fun, a_args }; };

      template<typename Visitor>
      class Call : public ExpImpl<Visitor, call_k> {};

      struct with_k
      { static const size_t arity = 2; enum types { a_obj, a_action }; };

      template<typename Visitor>
      class With : public ExpImpl<Visitor, with_k> {};

      struct in_k
      { static const size_t arity = 1; enum types { a_catalog }; };

      template<typename Visitor>
      class In : public ExpImpl<Visitor, in_k> {};

      /*----------------.
      | Value constants |
      `----------------*/

      template<typename Visitor>
      class Constant : public Exp<Visitor>
      {
      public:
	template<typename T>
	Constant(const T& data)
	  : obj_(data)
	{}

	Constant(const Constant& other)
	  : obj_(other.obj_)
	{}

	Constant() : obj_() {}

	Object obj() const
	{ return obj_; }

	virtual void accept(Visitor& v)
	{ v.visit(obj_); }

	virtual Exp<Visitor>* clone() const
	{ return new Constant(*this); }

	virtual ~Constant() {}
      protected:
	Object obj_;
      };

      /*-----------------.
      | Expression lists |
      `-----------------*/

      template<typename Visitor>
      class List : public Exp<Visitor>
      {
	public:

	List();
	List(const List& other);

	typedef std::list<Exp<Visitor>* > list_t;

	const list_t& list() const { return list_; }
	list_t& list() { return list_; }

	void push_back(const Exp<Visitor>& other);
	List* attach_front(Exp<Visitor>* exp);
	List* attach_back(Exp<Visitor>* exp);

	virtual Exp<Visitor>* clone() const
	{ return new List(*this); }

	virtual void accept(Visitor& v);

	~List();

      protected:
	list_t list_;
      };



    }
  }

}


#include <lazy/vauc_constructs.hxx>

#endif
