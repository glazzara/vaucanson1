// class_spec.cc
//
//

# include "class_spec.hh"

# include <iostream>
# include <set>
# include <string>
# include <iterator>

# include "spec/cpp_code.hh"

namespace spec {
  
  ClassSpec:: ClassSpec(const std::string& name, 
			const cpp_param_t& cpp_desc,
			const param_set_t& param,
			const std::string& prelude,
			const std::string& postlude, 
			const std::string& description) :
  cpp_desc_(cpp_desc),
  param_(param),
  param_value_(),
  description_(description)
  {
    param_value_["CLASS_NAME"]   = name;
    param_value_["PRELUDE"]      = prelude;
    param_value_["POSTLUDE"]     = postlude;
    param_value_["STATIC_TYPE"] = "Not defined yet.";
    name_     = param_value_.find("CLASS_NAME");
    prelude_  = param_value_.find("PRELUDE");
    postlude_ = param_value_.find("POSTLUDE");
  }
  
  const std::string
  ClassSpec:: name() const 
  {
    return (*name_).second;
  }
  
  const ClassSpec::cpp_param_t&
  ClassSpec:: cpp_desc() const 
  {
    return cpp_desc_;
  }

  const ClassSpec::param_set_t&
  ClassSpec::parameters() const
  {
    return param_;
  }
  
  const std::string
  ClassSpec::prelude() const
  {
    return (*prelude_).second;
  }
  
  const std::string
  ClassSpec::postlude() const
  {
    return (*postlude_).second;
  }
  
  const ClassSpec::param_value_t&
  ClassSpec::instanciate_class(const ClassSpec::param_value_t& param) 
  {
    spec::CppParamCode  cpp_name(this->name() + "$PARAM_VALUES$");

    param_value_["CPP_NAME"]    = cpp_name.instanciated_code(param);
    param_value_["STATIC_TYPE"] = cpp_desc_.instanciated_code(param);

    return param_value_;
  }

  const ClassSpec::param_value_t&
  ClassSpec::class_param() const
  {
    return param_value_;
  }

  const std::string&
  ClassSpec::description() const
  {
    return description_;
  }

  ClassSpec::param_value_t&
  ClassSpec::class_param() 
  {
    return param_value_;
  }

} // spec

namespace std
{

  std::ostream& 
  operator<<(std::ostream& o, const spec::ClassSpec& cs)
  {
    // FIXME : to be extended.
    o << "Class       : " << cs.name()		        << std::endl
      << "Parameters  : ";
    std::copy(cs.parameters().begin(), 
	      cs.parameters().end(), 
	      ostream_iterator<std::string>(o, " "));   
    return o;
  }

} // std
