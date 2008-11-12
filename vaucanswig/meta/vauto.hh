// vauto.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH
# define VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH

#include "vcontext.hh"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>

namespace vcsn
{
  struct virtual_automaton
  {
      virtual const virtual_context &context() const = 0;

      virtual bool has_state(int) const = 0;
      virtual bool has_transition(int) const = 0;
      virtual void del_state(int) = 0;
      virtual void del_transition(int) = 0;

      virtual std::list<int> states() const = 0;
      virtual std::list<int> transitions() const = 0;

      virtual int add_state() = 0;
      void add_states(int);
      virtual int add_spontaneous(int, int) = 0;
      virtual int add_letter_transition(int, int, char) = 0;
      virtual int add_lw_transition(int, int, int, const std::string&) = 0;
      virtual int add_rw_transition(int, int, const std::string&, int) = 0;
      virtual int add_lrw_transition(int, int, int, const std::string&, int) = 0;

      virtual std::string label_of(int) const = 0;

      virtual int src_of(int) const = 0;
      virtual int dst_of(int) const = 0;

      virtual void clear_initial() = 0;
      virtual std::list<int> initial() const = 0;
      virtual bool is_initial(int) const = 0;
      virtual void unset_initial(int) = 0;
      virtual void set_initial(int) = 0;
      virtual void set_initial(int, char) = 0;
      virtual void set_initial_lw(int, int, char) = 0;
      virtual void set_initial_lw(int, int) = 0;
      virtual void set_initial_rw(int, char, int) = 0;
      virtual void set_initial_rw(int, int) = 0;
      virtual void set_initial_lrw(int, int, char, int) = 0;
      virtual void set_initial_lrw(int, int, int) = 0;
      virtual std::string initial_label(int) = 0;

      virtual void clear_final() = 0;
      virtual std::list<int> final() const = 0;
      virtual bool is_final(int) const = 0;
      virtual void unset_final(int) = 0;
      virtual void set_final(int) = 0;
      virtual void set_final(int, char) = 0;
      virtual void set_final_lw(int, int, char) = 0;
      virtual void set_final_lw(int, int) = 0;
      virtual void set_final_rw(int, char, int) = 0;
      virtual void set_final_rw(int, int) = 0;
      virtual void set_final_lrw(int, int, char, int) = 0;
      virtual void set_final_lrw(int, int, int) = 0;
      virtual std::string final_label(int) = 0;

      virtual std::string describe(bool cpptype = false) const = 0;

      virtual void load(std::istream&, const std::string& format) = 0;
      virtual void save(std::ostream&, const std::string& format) const = 0;

      void string_load(const std::string& in, const std::string& format);
      std::string string_save(const std::string& format) const;

      void dot_run(const char *fname, const char *cmd = "gv", const char *name = "automaton") const;
      virtual ~virtual_automaton();
  };
}

#endif // ! VCSN_DEMOS_VAUCANSWIG_META_VAUTO_HH
