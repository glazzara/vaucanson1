// usual_io.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_TOOLS_USUAL_IO_HH
# define VCSN_TOOLS_USUAL_IO_HH

# include <string>

namespace vcsn
{
  namespace io
  {
    struct usual_converter_exp
    {
      template<typename Auto>
      typename Auto::series_set_elt_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::series_set_elt_t& exp_series) const;
    };

    template<typename ExpType>
    struct usual_converter_poly
    {
      template<typename Auto>
      typename Auto::series_set_elt_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::series_set_elt_t& poly_series) const;
    };
  }
}


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/tools/usual_io.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // ! VCSN_TOOLS_USUAL_IO_HH
