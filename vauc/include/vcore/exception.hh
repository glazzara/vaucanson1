/***********************
 * <vcore/exception.hh> *
 ***********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef CORE_EXCEPTION_HH
#define CORE_EXCEPTION_HH

#include <stdexcept>
#include <list>
#include <string>
#include <utility>
#include <iostream>

namespace vcsn
{
  namespace vauc
  {
    class Exception 
      : public std::exception
    {
    public:
      typedef std::list<std::pair<std::string, std::string> > descr_t;

      Exception(const std::string& Where, const std::string& What);

      void attach(const std::string& Where, const std::string& What);

      const descr_t& description() const;

      ~Exception() throw() ;

      void print(std::ostream& s) const;

    protected:
      descr_t descr_;
    };

  }
}

#define RAISE(Where, What) throw Exception(Where, What)
#define EXCEPTION(e) vcsn::vauc::Exception& e
#define ATTACH(e, Where, What) e.attach(Where, What)


#endif
