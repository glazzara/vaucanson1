/**************************
 * "core/partial_call.cc" *
 **************************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/partial_call.hh>
#include <vcore/exception.hh>
#include <cassert>
#include <sstream>
#include <iostream>

namespace vcsn
{
  namespace vauc
  {

    /*------------------.
    | class PartialCall |
    `------------------*/

    const PartialCall::sig_t& PartialCall::signature() const
    {
      assert(c_.bound());
      return partial_sig_;
    }

    PartialCall::PartialCall(Callable c)
      : c_(c), partial_sig_(c.signature())
    {
      description_ = c.description();
      origin_ = c.origin();
    }

// #ifndef DEBUG
// #define DEBUG 1
// #endif

#ifdef DEBUG
#define d(x) do { std::cerr << x << std::endl; } while(0)
#else
#define d(x)
#endif


    void PartialCall::append_arg(Object arg)
    {
      d("-- partial augmentation --");
      assert(c_.bound());
      assert(partial_sig_.size() > 0);
      
      d("we are in (" << description_ << ')');
      d("there are " << partial_args_.size() << " preset args.");
      d("the remaining sig has " << partial_sig_.size() << " types.");

      partial_args_.push_back(arg);
      partial_sig_.erase(partial_sig_.begin());

      d("now there are " << partial_args_.size() << " preset args.");
      d("now the remaining sig has " << partial_sig_.size() << " types.");

      std::ostringstream o;
      o << c_.description() 
	<< ", " 
	<< partial_args_.size() << " arguments preset";
      description_ = o.str();

      d("** it is now (" << description_ << ')');

      // FIXME
      origin_ = '(' + origin_ + ")..[<...>]";


    }
    void PartialCall::append_args(const std::vector<Object>& args)
    {
      d("-- partial augmentation --");

      assert(c_.bound());
      assert(partial_sig_.size() >= args.size());

      d("we are in (" << description_ << ')');
      d("there are " << partial_args_.size() << " preset args.");
      d("the remaining sig has " << partial_sig_.size() << " types.");
      d(args.size() << " are being appended");

      if (args.size() == 0)
	{
	  d("** doing nothing");
	  return ;
	}
      for (std::vector<Object>::const_iterator i = args.begin();
	   i != args.end(); 
	   ++i)
	{
	  d("> stdying given arg " << i - args.begin());
	  d("it has type: " << i->cpp_type().name());
	  d("wanted type: " << partial_sig_[i - args.begin()]); 
	  assert (partial_sig_[i - args.begin()] == "" ||
		  partial_sig_[i - args.begin()] == i->cpp_type().name());
	  partial_args_.push_back(*i);
	}
      d("now there are " << partial_args_.size() << " preset args.");

      partial_sig_.erase(partial_sig_.begin(), 
			 partial_sig_.begin() + args.size());

      d("now the remaining sig has " << partial_sig_.size() << " types.");

      std::ostringstream o;
      o << c_.description() 
	<< ", " 
	<< partial_args_.size() << " arguments preset";
      description_ = o.str();

      // FIXME: change origin_

      d("** it is now (" << description_ << ')');
    }

    
    Object PartialCall::call(Env& context,
			     const std::vector<Object>& args) const
    {
      assert(c_.bound());
      assert(partial_sig_.size() == args.size());

      std::vector<Object> all_args(partial_args_);
      all_args.insert(all_args.end(), args.begin(), args.end());

      return c_.call(context, all_args);
    }


    std::string PartialCall::return_type(const PartialCall::sig_t& sig) const
    {
      assert(c_.bound());
      assert(partial_sig_.size() == sig.size());

      std::vector<std::string> full_sig;
      for (std::vector<Object>::const_iterator i = partial_args_.begin();
	   i != partial_args_.end();
	   ++i)
	full_sig.push_back(i->cpp_type().name());

      full_sig.insert(full_sig.end(), sig.begin(), sig.end());

      try
	{
	  return c_.return_type(full_sig);
	}
      catch (...)
	{
	  return "";
	}
    }

    const std::string& PartialCall::description() const
    {
      return description_;
    }

    const std::string& PartialCall::origin() const
    {
      return origin_;
    }

    PartialCall::PartialCall(const PartialCall& other)
      : c_(other.c_),
	partial_args_(other.partial_args_),
	partial_sig_(other.partial_sig_),
	description_(other.description_)
    {}

    PartialCall::PartialCall()
      : c_(),
	description_("(function not bound)")
    { }

    PartialCall& PartialCall::operator=(const PartialCall& other)
    {
      c_ = other.c_;
      partial_args_ = other.partial_args_;
      partial_sig_ = other.partial_sig_;
      description_ = other.description_;
      return *this;
    }

    bool PartialCallCompare::operator()(const PartialCall& lhs, const PartialCall& rhs) const
    {
      typedef std::vector<std::string>::const_iterator const_iterator;
      const_iterator i, j;

      for (i = lhs.signature().begin(),
	   j = rhs.signature().begin();
	   i != lhs.signature().end() 
	     && j != rhs.signature().end();
	   ++i, ++j)
	{
	  if (*i < *j)
	    return true;
	  if (*j < *i)
	    return false;
	}
      return lhs.signature().end() != i;
    }

    PartialCall::~PartialCall()
    {}

  }
}

