/*********************
 * "core/closure.cc" *
 *********************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/closure.hh>
#include <vcore/exception.hh>
#include <vcore/env.hh>
#include <list>
#include <limits>

namespace vcsn
{
  namespace vauc
  {
    // see the comments in <vcore/closure.hh>


    Closure::Closure()
    {}

    Closure::Closure(const Closure& other)
      : funs_(other.funs_), partial_args_(other.partial_args_)
    {}

    Closure& Closure::operator=(const Closure& other)
    {
      funs_ = other.funs_;
      partial_args_ = other.partial_args_;
      return *this;
    }


// #ifndef DEBUG
// #define DEBUG 1
// #endif

#ifdef DEBUG
#define d(x) do { std::cerr << x << std::endl; } while(0)
#else
#define d(x)
#endif


    void Closure::restrict(const std::vector<Object>& args)
    {
      d("-- closure restriction -- ");

      funs_t::iterator j;
      
      d("arguments given for the restriction: " << args.size());
      d("arguments preset: " << partial_args_.size());
      d("there are " << funs_.size() << " functions to study");

      size_t all_args = args.size() + partial_args_.size();
      for (funs_t::iterator i = funs_.begin(); i != funs_.end(); )
	{
	  d("> studying callable (" << i->description() << ')');
	  j = i++;
	  d("its signature has " << j->signature().size() << ") types");
	  if (j->signature().size() < all_args)
	    {
	      d("it cannot be used, it is removed");
	      funs_.erase(j);
	    }
	}
      d("now " << funs_.size() << " callables remain in the closure");
      if (funs_.empty())
	RAISE("closure restriction", "too many arguments");

      partial_args_.insert(partial_args_.end(), args.begin(), args.end());
      d("** there are now " << partial_args_.size() << " partial arguments.");
    }
			       
    void Closure::trim()
    {
      funs_t::iterator j;

      d("-- closure trim --");
      d("arguments preset: " << partial_args_.size());
      d("there are " << funs_.size() << " functions to study");

      for (funs_t::iterator i = funs_.begin(); i != funs_.end(); )
	{
	  d("> studying callable (" << i->description() << ')');
	  j = i++;
	  d("its signature has " << j->signature().size() << ") types");
	  if (! j->signature().empty())
	    {
	      d("it takes arguments, it is thus removed.");
	      funs_.erase(j);
	    }
	}
      d("** there remain " << funs_.size() << " callables.");
    }

    void Closure::freeze(Env& env)
    {
      const unsigned max = std::numeric_limits<unsigned>::max();

      d("-- closure freeze --");
      
      unsigned current_minimum = max;
      std::list<PartialCall> best_matches;

      funs_t::iterator f_iter, f_cur;

      FunctionImpl::sig_t::const_iterator t_iter;
      std::vector<Object>::const_iterator a_iter;

      // first, collect those partial calls which cost less to convert
      d("there are " << funs_.size() << " functions to study");
      d("there are " << partial_args_.size() << " preset arguments");
      for (f_iter = funs_.begin(); f_iter != funs_.end(); )
	{
	  f_cur = f_iter++;

	  d("> studying function (" << f_cur->description() << ')');
	  unsigned sum = 0;
	  for (t_iter = f_cur->signature().begin(),
		 a_iter = partial_args_.begin();
	       /* always true:   t_iter != f_cur->signature().end() */
		 a_iter != partial_args_.end();
	       ++t_iter, ++a_iter)
	    {
	      d("arg: expected: " << *t_iter << ", got " << a_iter->cpp_type().name());
	      unsigned d = env.type_distance(a_iter->cpp_type().name(), 
					     *t_iter);
	      d("cost to do this conversion: " << d);
	      if (d == max)
		{
		  d("cost means conversion impossible");
		  sum = max;
		  break ;
		}
	      sum += d; // FIXME: this may overflow
	      d("overall cost now: " << sum);
	    }
	  d("current minimum cost for the closure: " << current_minimum);
	  if (sum <= current_minimum)
	    {
	      d("last cost was at least cheaper");
	      if (sum < current_minimum) // a lower cost has been found
		{
		  d("it *was* cheaper, changing the minimum");
		  best_matches.clear();
		  current_minimum = sum;
		}
	      d("a new possible match was found (" << f_cur->description() << ')');
	      best_matches.push_front(*f_cur);
	    }
	}
      // first check that a conversion is indeed possible:
      d("-- the current minimum cost is now:" << current_minimum);
      if (current_minimum == max)
	RAISE("closure freeze", "no matching function for call");

      // here best_matches contains iterators to 'interesting' partial apps
      for (std::list<PartialCall>::iterator p_iter = best_matches.begin();
	   p_iter != best_matches.end();
	   ++p_iter)
	{
	  std::vector<Object> converted_args;
	  
	  d("doing the conversion for candidate (" << p_iter->description() << ')');
	  for (t_iter = p_iter->signature().begin(), 
                 a_iter = partial_args_.begin(); 
	       a_iter != partial_args_.end(); 
               ++t_iter, ++a_iter) 
	    {
	      d("original type: " << a_iter->cpp_type().name());
	      converted_args.push_back(env.obj_convert(*a_iter, *t_iter));
	      d("resulting type:" << converted_args.back().cpp_type().name());
	    }
	  d("now the args are being pushed into the candidate");
	  // now we can commit the arguments
	  p_iter->append_args(converted_args);
	  d("the candidate now is (" << p_iter->description() << ')');
	  d("it takes " << p_iter->signature().size() << " argumants");
	}

      // now commit the best matches to the real set
      funs_.clear();
      funs_.insert(best_matches.begin(), best_matches.end());
      partial_args_.clear();
      d("there remain " << partial_args_.size() << " partial args.");
      d("** there are now " << funs_.size() << " callables in this closure.");
    }


    Callable Closure::resolve_call(Env& env, 
				   const std::vector<Object>& args) const
    {
      Closure work(*this);

      d("-- resolving call --");
      d("arguments given for the call: " << args.size());
      d("arguments preset: " << partial_args_.size());
      d("there are " << funs_.size() << " functions to study");

      if (! args.empty())
	work.restrict(args);
      work.freeze(env);
      work.trim();
      if (work.funs_.empty())
	RAISE("resolving call", "nothing to call");
      if (work.funs_.size() > 1)
	RAISE("resolving call", "ambiguous call");

      return Callable(new PartialCall(*work.funs_.begin()));
    }

    void Closure::merge_fun(const PartialCall& p)
    {
      if (p.signature().size() < partial_args_.size())
	RAISE("in function merge", "new function takes too few arguments");
      funs_.erase(p);
      funs_.insert(p);
    }

    const Closure::funs_t& Closure::funs() const
    {
      return funs_;
    }
    
    const std::vector<Object>& Closure::partial_args() const
    {
      return partial_args_;
    }

  }
}

