// tags.hxx
// 
// VCSN_HEADER

#ifndef AUTOMATA_TAGS_HXX
#define AUTOMATA_TAGS_HXX

# include <vaucanson/automata/concept/tags.hh>

static inline bool operator==(const vcsn::NoTag& a, const vcsn::NoTag& b)
{ return true; }
static inline bool operator!=(const vcsn::NoTag& a, const vcsn::NoTag& b)
{ return false; }

#endif
