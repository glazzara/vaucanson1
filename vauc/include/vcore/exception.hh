/***********************
 * <core/exception.hh> *
 ***********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_EXCEPTION_HH
#define CORE_EXCEPTION_HH

// import from cppsh
# include <kern/exception.hh>

namespace vcsn
{
  namespace vauc
  {

    using cppsh::Exception;
  }
}

#define RAISE(Where, What) cppsh::failwith(Where, Where, What)
#define EXCEPTION(e) cppsh::Exception& e
#define ATTACH(e, Where, What) e.add_trace(Where, What)
#define RETHROW(e) cppsh::rethrow(e)

#endif
