// meta_set.hh
// 
// MICAL_HEADER

#ifndef   META_SET_HH_
# define   META_SET_HH_

# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

  template<typename S, unsigned K>
  struct MetaSet
  {
    static const bool dynamic_set = true;
  };

} // vcsn

#endif /* !META_SET_HH_ */
