/************************************
 * <vaucanson/automata/handlers.hxx> *
 ************************************/

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_HANDLERS_HXX
#define AUTOMATA_HANDLERS_HXX

# include <iostream>

namespace vcsn
{
  
  template<typename Tag>
  handler<Tag>::handler() : v_(0) 
  {}

  template<typename Tag>
  handler<Tag>::handler(unsigned h) : v_(h) 
  {}

  template<typename Tag>
  handler<Tag>::handler(const handler& h) : v_(h.v_) 
  {}
    
  template<typename Tag>
  handler<Tag>& handler<Tag>::operator=(const handler<Tag>& h)
  { 
    v_ = h.v_; 
    return *this; 
  }

  template<typename Tag>
  handler<Tag>& handler<Tag>::operator=(unsigned h)
  { 
    v_ = h; 
    return *this; 
  }
    
  template<typename Tag>
  unsigned handler<Tag>::value() const 
  { 
    return v_; 
  }
    
  template<typename Tag>
  handler<Tag>::operator unsigned int () const 
  { 
    return v_; 
  }


} // vcsn

#define HOPERATOR(Op)								\
template<typename kind>								\
bool operator Op (const vcsn::handler<kind>& h1, const vcsn::handler<kind>& h2)	\
{ return h1.value() Op h2.value(); }

HOPERATOR(==);
HOPERATOR(!=);
HOPERATOR(<);
HOPERATOR(>);
HOPERATOR(<=);
HOPERATOR(>=);

namespace std {

  template <typename kind>
  std::ostream&	
  operator<<(std::ostream& out, const vcsn::handler<kind>& h)
  {
    out << h.value();
    return out;
  }

} // std

#undef HOPERATOR
#endif
