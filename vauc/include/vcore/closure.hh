/*********************
 * <vcore/closure.hh> *
 *********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_CLOSURE_HH
#define CORE_CLOSURE_HH

#include <vcore/partial_call.hh>
#include <set>

namespace vcsn
{

  namespace vauc
  {

    class Closure
    {
    public:
      typedef std::set<PartialCall, PartialCallCompare> funs_t;

      Closure();
      Closure(const Closure& other);

      Closure& operator=(const Closure& other);
      
      // restricts a closure. raises an exception if the
      // closure is empty after removing useless functions.
      void restrict(const std::vector<Object>& args);

      // freeze a closure, that is, attempt to commit the partial
      // arguments to each PartialCall, doing necessary selections
      // & type conversions.
      // the resulting closure may be empty.
      void freeze(Env& env);

      
      // trim a closure, that is, remove all partial calls which have
      // remaining empty argument slots. The partial argument list is
      // cleared. Of course trim() should take place after freeze().
      // the resulting closure may be empty.
      void trim();

      // attempt to resolve a call. 
      // If the argument list specified is not empty,
      // attempt to restrict.
      // then the closure is frozen, then trimmed, 
      // and the resolve is attempted.
      // The resulting callable takes no argument.
      Callable resolve_call(Env& env, const std::vector<Object>& args) const;

      // insert a new partial call in the function
      void merge_fun(const PartialCall& other);

      // accessors for help to the pretty-printer:
      const funs_t& funs() const;
      const std::vector<Object>& partial_args() const;

    protected:
      funs_t funs_;
      std::vector<Object> partial_args_;
    };
  }
}

#endif

