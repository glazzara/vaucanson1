// fundamental/meta_set.hh
//
// VCSN_HEADER
#ifndef FUNDAMENTAL_META_SET_HH
# define FUNDAMENTAL_META_SET_HH

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

  // the following template MUST be specialized.
  template<typename S>
  struct MetaSet
  {
    static const bool dynamic_set = true;
  };

} // vcsn

#endif // FUNDAMENTAL_META_SET_HH
