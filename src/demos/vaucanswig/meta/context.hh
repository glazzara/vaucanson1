#ifndef CONTEXT_HH
# define CONTEXT_HH

#include "vcontext.hh"
#include <string>
#include <sstream>

template<typename Auto>
struct vcsn_context : vcsn::virtual_context
{
  AUTOMATON_TYPES(Auto)

    vcsn_context(const automata_set_t& set)
      : set_(& utility::unique::get(set))
  {}
  vcsn_context(const vcsn_context& other)
    : set_(other.set_)
  {}
  
  template<typename OtherAuto>
  vcsn_context(const vcsn_context<OtherAuto>& other)
    : set_(& other.automata_set())
  {}

  const automata_set_t& automata_set() const
  { return *set_; }
  
  const series_t& series() const
  { return set_->series(); }
  
  const monoid_t& monoid() const
  { return set_->series().monoid(); }
  
  const alphabet_t& alphabet() const
  { return set_->series().monoid().alphabet(); }
  
  const weights_t& weights() const
  { return set_->series().weights(); }
  
  virtual std::list<char> alphabet_letters() const
  { return std::list<char>(alphabet().begin(), alphabet().end()); }

  virtual std::string describe_alphabet(bool cpp) const
  { 
    std::ostringstream ret;
    ret << "Alphabet (" << alphabet() << ')';
    if (cpp)
      ret << " <" << typeid(alphabet_t).name() << '>';
    return ret.str();
  }

  virtual std::string describe_weights(bool cpp) const
  { 
    std::string ret = "Semiring";
    if (cpp)
      ret = ret + " <" + typeid(weights_t).name() + '>';
    return ret;
  }

  virtual std::string describe_monoid(bool cpp) const
  { 
    std::string ret = "Monoid (" + describe_alphabet(cpp) + ')';
    if (cpp)
      ret = ret + " <" + typeid(monoid_t).name() + '>';
    return ret;
  }

  virtual std::string describe_series(bool cpp) const
  { 
    std::string ret = "Series (" + describe_weights(cpp) 
      + ", " + describe_monoid(cpp) + ')';
    if (cpp)
      ret = ret + " <" + typeid(series_t).name() + '>';
    return ret;
  }

  virtual std::string describe_automata_set(bool cpp) const
  {
    std::string ret = "AutomataSet (" + describe_series(cpp) + ')';
    if (cpp)
      ret = ret + " <" + typeid(automata_set_t).name() + '>';
    return ret;
  }    

  virtual ~vcsn_context() {}

protected:
  const automata_set_t* set_;
};

#define MAKE_AUTO_TYPES(FAMILY)					\
namespace FAMILY ##_types					\
{								\
  typedef vcsn::tools::FAMILY ##_automaton_t automaton_t;	\
  AUTOMATON_TYPES_EXACT_(automaton_t, FAMILY ##_)		\
}

#define MAKE_GEN_AUTO_TYPES(FAMILY)						\
namespace FAMILY ##_types							\
{										\
  typedef vcsn::generalized_traits<automaton_t>::automaton_t generalized_automaton_t;	\
  AUTOMATON_TYPES_EXACT_(generalized_automaton_t, gen_## FAMILY ##_)		\
  typedef gen_## FAMILY ##_serie_t FAMILY ##_exp_t;                             \
  typedef gen_## FAMILY ##_serie_value_t FAMILY ##_exp_value_t;                 \
}


#define MAKE_CONTEXT_TYPE(FAMILY)			\
namespace FAMILY ##_types				\
{							\
  typedef vcsn_context<automaton_t> FAMILY ##_context;	\
}

#define MAKE_CONTEXT_OPS(FAMILY)			\
namespace FAMILY ##_types				\
{							\
  FAMILY ##_alphabet_t letters(const char *s)		\
  {							\
    FAMILY ##_alphabet_t alpha;				\
    while (*s)						\
      alpha.insert(*s++);				\
    return alpha;					\
  }							\
							\
  FAMILY ##_context					\
  make_context(const FAMILY ##_alphabet_t& alpha)	\
  {							\
    FAMILY ##_weights_t semiring;			\
    FAMILY ##_monoid_t monoid(alpha);			\
    FAMILY ##_series_t series(semiring, monoid);	\
    FAMILY ##_automata_set_t automata_set(series);	\
    return FAMILY ##_context(automata_set);		\
  }							\
}

#define MAKE_SE_IO(FAMILY)										\
namespace FAMILY ##_types										\
{													\
  inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_monoid_t& m)				\
  { return o << '<' << typeid(m).name() << "> FreeMonoid (" << m.alphabet() << ')'; }			\
													\
  inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_weights_t& w)			\
  { return o << '<' << typeid(w).name() << "> Semiring"; }						\
													\
  inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_series_t& s)				\
  { return o << '<' << typeid(s).name() << "> Series (" << s.weights() << ", " << s.monoid() << ')'; }	\
    													\
  inline std::ostream& operator<<(std::ostream& o, const FAMILY ##_automata_set_t& a)			\
  { return o << '<' << typeid(a).name() << "> AutomataSet (" << a.series() << ')'; }			\
													\
}

#endif
