// fundamental/predefs.hh
//
// VCSN_HEADER
#ifndef FUNDAMENTAL_PREDEFS_HH
# define FUNDAMENTAL_PREDEFS_HH

namespace vcsn {

  template<typename S>
  struct MetaSet;
  
  template<typename S, typename T>
  struct MetaElementBase;
  
  template<typename S, typename T>
  struct MetaElement;

  template<typename S, typename T>
  struct Element;
  
  template<typename S>
  struct SetSlot;
  
  template<typename S, typename T>
  struct ValueSlot;

  template<typename Self>
  struct Structure;

} // vcsn

#endif // FUNDAMENTAL_PREDEFS_HH
