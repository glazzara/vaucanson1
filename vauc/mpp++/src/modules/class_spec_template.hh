// #CLASSNAME#.hh
// for
// $STATIC_TYPE$ 
//

#ifndef #CLASS_NAME#_$STATIC_TYPE$_HH
# define #CLASS_NAME#_$STATIC_TYPE$_HH

#include "
#PRELUDE#

    class #CLASSNAME#Type : public Type
    {
    public:
     typedef #STATIC_TYPE#       static_type_t;
     typedef #CLASSNAME#Type     dynamic_type_t;

    public:      
      virtual const std::string& name() const 
      { 
	static const std::string instance = 
	  std::string(\"#CLASSNAME#\");
	return instance; 
      }
      
      virtual const std::string& nickname() const
      {
	static const std::string instance = \"#CLASSNAME#\";
	return instance;
      }
      
      virtual bool compare_to(const Type& other) const
      { 
	return (NULL != dynamic_cast<const dynamic_type_t*>(&other)); 
      }
           
      virtual const Type& instance() const
      {
	static const dynamic_type_t instance;
	return instance;
      }
      
      virtual const std::type_info& cpp_type() const
      { 
	return typeid(static_type_t); 
      }
    };

    template <>
    struct TypeTraits<#STATIC_TYPE#>
    {
      typedef #CLASSNAME#Type	type_t;
    };

#POSTLUDE#

#endif 
