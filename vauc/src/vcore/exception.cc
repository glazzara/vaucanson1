/***********************
 * "core/exception.cc" *
 ***********************/
// $Id$

/* this file is part of the Vaucanson project */

#include <vcore/exception.hh>


namespace vcsn
{
  namespace vauc
  {
    Exception::Exception(const std::string& Where, const std::string& What)
    {
      descr_.push_back(std::make_pair(Where, What));
    }
    
    void Exception::attach(const std::string& Where, const std::string& What)
    {
      descr_.push_back(std::make_pair(Where, What));
    }

    const Exception::descr_t&
    Exception::description() const
    {
      return descr_;
    }

    void Exception::print(std::ostream& o) const
    {
      size_t max_loc_width = 0;
      for (descr_t::const_iterator i = descr_.begin();
	   i != descr_.end();
	   ++i)
	if (i->first.size() > max_loc_width)
	  max_loc_width = i->first.size();

      for (descr_t::const_reverse_iterator i = descr_.rbegin();
	   i != descr_.rend();
	   ++i)
	{
	  o << i->first;
	  for (size_t l = 0; l < max_loc_width - i->first.size(); ++l)
	    o << ' ';
	  o << " : " << i->second << std::endl;
	}
    }

    Exception::~Exception() throw()
    {}

  }
}
