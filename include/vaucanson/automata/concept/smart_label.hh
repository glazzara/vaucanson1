// smart_label.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

#ifndef VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HH_
# define VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HH_

# include <boost/multi_index_container.hpp>
# include <boost/multi_index/member.hpp>
# include <boost/multi_index/mem_fun.hpp>
# include <boost/multi_index/hashed_index.hpp>
# include <boost/shared_ptr.hpp>

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/misc/hash.hh>

namespace vcsn
{
  template <typename T> // T = Graph::label_t
  class SmartLabel
  {
    public:
      typedef T value_type;

      explicit SmartLabel(const ::boost::shared_ptr<T>& l);

      const T& value () const;

      // Handle the reference count
      int ref () const;
      int ref_dec ();
      int ref_inc ();

   private:
      ::boost::shared_ptr<T> value_;
      int ref_;
  };

  template <typename T> // T = Graph::label_t
  class SmartLabelContainer
  {
    public:
      typedef T value_type;

    private:
      struct label {};
      typedef ::boost::multi_index_container<
	  SmartLabel<T>,
	  ::boost::multi_index::indexed_by<
	    ::boost::multi_index::hashed_unique<
	      ::boost::multi_index::tag<label>,
	      BOOST_MULTI_INDEX_CONST_MEM_FUN (SmartLabel<T>, const T&, value),
	      misc::hash_label<T>
	    >
	  >
	> label_container_t;

      label_container_t data_;

    public:
      struct label_h
      {};
      typedef handler<label_h, const SmartLabel<T>*> hlabel_t;

      hlabel_t insert (const T&);
      void erase (const hlabel_t&);
      hlabel_t update (const hlabel_t&, const T&);

      const T& get_label (const hlabel_t&) const;
      hlabel_t get_hlabel (const T&) const;
  };

} // End of namespace vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/concept/smart_label.hxx>
# endif // !VCSN_USE_INTERFACE_ONLY || VCSN_USE_LIB

#endif // !VCSN_AUTOMATA_CONCEPT_SMART_LABEL_HH_ //
