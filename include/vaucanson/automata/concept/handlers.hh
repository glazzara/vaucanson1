// handlers.hh
//
// $Id$
// VCSN_HEADER
#ifndef AUTOMATA_HANDLERS_HH
#define AUTOMATA_HANDLERS_HH

# include <iostream>

namespace vcsn
{
  struct state_h { };
  struct edge_h { };

  template<typename Tag>
  class handler
  {
  public:
    typedef Tag kind;

    handler();

    handler(unsigned h);

    handler(const handler& h);
    
    handler& operator=(const handler& h);

    handler& operator=(unsigned h);
    
    unsigned value() const;

    operator unsigned int () const;

  protected:
    unsigned v_;
  };

  typedef handler<state_h> hstate_t;
  typedef handler<edge_h> hedge_t;

} // vcsn

#define HOPERATOR(Op)								\
template<typename kind>								\
bool operator Op (const vcsn::handler<kind>& h1, const vcsn::handler<kind>& h2);	\


HOPERATOR(==);
HOPERATOR(!=);
HOPERATOR(<);
HOPERATOR(>);
HOPERATOR(<=);
HOPERATOR(>=);

namespace std {

  template <typename kind>
  std::ostream&	
  operator<<(std::ostream& out, const vcsn::handler<kind>& h);

} // std

#undef HOPERATOR

# include <vaucanson/automata/concept/handlers.hxx>

#endif
