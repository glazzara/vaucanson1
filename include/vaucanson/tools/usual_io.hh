#ifndef USUAL_IO_HH
# define USUAL_IO_HH

# include <string>

namespace vcsn
{
  namespace io
  {
    struct usual_converter_exp
    {
      template<typename Auto>
      typename Auto::serie_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::serie_t& exp_serie) const;
    };

    template<typename ExpType>
    struct usual_converter_poly
    {
      template<typename Auto>
      typename Auto::serie_t operator()(const Auto&, const std::string& lbl) const;
      template<typename Auto>
      std::string operator()(const Auto&, const typename Auto::serie_t& poly_serie) const;
    };
  }
}

# include <vaucanson/tools/usual_io.hxx>

#endif
