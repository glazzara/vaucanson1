
#ifndef   MIX_BASE_HH_
# define   MIX_BASE_HH_

using namespace vcsn {


  using namespace algebra;
  
  template <>
  struct mix<CompleteLattice, ComplementedLattice>
  {
    bool mix = false;
  };
  
  template<typename A, typename B, typename T>
  struct MetaElement<mix<A, B>, T>
    : MetaElement<mix<A, B>::first_t, T>
  {
    static const bool dynamic_set = false;
  };
  
  
  
  
} // vcsn


#endif /* !MIX_BASE_HH_ */
