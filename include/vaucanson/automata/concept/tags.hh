/********************************
 * <vaucanson/automata/tags.hh> *
 ********************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef AUTOMATA_TAGS_HH
#define AUTOMATA_TAGS_HH


namespace vcsn
{
  struct NoTag
  {};

} // vcsn

static inline bool operator==(const vcsn::NoTag& a, const vcsn::NoTag& b);
static inline bool operator!=(const vcsn::NoTag& a, const vcsn::NoTag& b);

# include <vaucanson/automata/concept/tags.hxx>

#endif
