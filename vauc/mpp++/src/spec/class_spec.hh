// class_spec.hh
//
//
#ifndef SPEC_CLASS_SPEC_HH
# define SPEC_CLASS_SPEC_HH

# include <set>
# include <string>

# include "spec/cpp_code.hh"

namespace spec {

  class ClassSpec 
  {
  public:

    typedef CppParamCode		cpp_param_t;
    typedef cpp_param_t::param_set_t	param_set_t;
    typedef cpp_param_t::param_value_t	param_value_t;

  public :
    ClassSpec(const std::string& name, 
	      const cpp_param_t& cpp_desc,
	      const param_set_t& param,
	      const std::string& prelude,
	      const std::string& postlude, 
	      const std::string& description);

    const std::string
    name() const;

    const std::string
    prelude() const;

    const std::string
    postlude() const;

    const param_value_t&
    instanciate_class(const param_value_t&);

    const param_value_t&
    class_param() const;

    param_value_t&
    class_param();

    const param_set_t&
    parameters() const;

    const cpp_param_t&
    cpp_desc() const;
    
    const std::string&
    description() const;

  private :
    cpp_param_t				cpp_desc_;
    param_set_t				param_;
    param_value_t			param_value_;
    param_value_t::const_iterator	prelude_;
    param_value_t::const_iterator	postlude_;
    param_value_t::const_iterator	name_;
    std::string				description_;
  };

} // spec

namespace std 
{

  std::ostream& 
  operator<<(std::ostream& o, const spec::ClassSpec& cs);

} // std

#endif // SPEC_CLASS_SPEC_HH
