// spec/module_spec.hh
//
//
#ifndef SPEC_MODULE_SPEC_HH
# define SPEC_MODULE_SPEC_HH

# include <list>
# include <string>
# include <iostream>

# include "spec/cpp_code.hh"
# include "internal/mangling.hh"

namespace spec 
{    
  
  struct Version 
  {
    virtual
    ~Version() {}
  };

  struct FunVersion : public Version
  {
    typedef std::list<std::string>		signature_t;
    typedef std::list<std::list<std::string> >  sigs_t;
    typedef std::map<std::string, std::string>  args_t;

    args_t					args;
    std::string					name;
    std::string					dynamic_name;
    sigs_t					sigs;
  };

  struct TypeVersion : public Version
  {
    typedef std::map<std::string, std::string>  args_t;

    std::string					dynamic_name;
    std::string					name;
    args_t				       	args;
  };

  struct ObjectVersion : public Version
  {
    std::string					name;
    std::string					dynamic_type;
    std::string       			       	value;
  };

  struct Alias : public Version
  {
    std::string		alias;
    std::string		realname;
  };

  class ModuleSpec
  {
  public:
    typedef std::list<FunVersion>		fun_version_list_t;
    typedef std::list<TypeVersion>		type_version_list_t;
    typedef std::list<ObjectVersion>		object_version_list_t;
    typedef std::map<std::string, std::string>	aliases_t;
    typedef std::list<std::string>		param_set_t;
    typedef std::map<std::string, std::string>	param_value_t;


  public:
    ModuleSpec(const std::string&		name, 
	       const fun_version_list_t&	fun_versions, 
	       const type_version_list_t&	type_versions,
	       const object_version_list_t&	object_versions,
	       const aliases_t&			aliases, 
	       const std::string&		prelude,
	       const std::string&		description);

    const std::string&	
    name() const;

    const std::string&
    prelude() const;

    const fun_version_list_t&
    fun_versions() const;

    const object_version_list_t&
    object_versions() const;

    fun_version_list_t&
    fun_versions();
    
    const type_version_list_t&
    type_versions() const;

    type_version_list_t&
    type_versions();

    const aliases_t&
    aliases() const;

    aliases_t&
    aliases();

    const std::string&
    description() const;

  private:
    std::string			name_;
    fun_version_list_t		fun_versions_;
    type_version_list_t		type_versions_;
    object_version_list_t	object_versions_;
    aliases_t			aliases_;
    std::string			prelude_;
    std::string			description_;
  };


  /*---------.
  | ModuleDB |
  `---------*/
  struct Tuple
  {
    std::string	realname;
    std::string	filename;
  };

  class ModuleDB
  {
  public :
    typedef  std::map<std::string, Tuple>	db_t;

  public:
    void 
    insert(const std::string&, const std::string&);

    std::string 
    get_realname(const std::string&);

    std::string 
    get_filename(const std::string&);
    
    void 
    save(std::ostream&);
    
    void 
    load(std::istream&);
    
    std::string 
    mangle(const std::string& realname);
    
    std::string 
    demangle(const std::string& filename);

  private:
    db_t	map_;
    Mangler	mangler_;
  };

} // spec

namespace std 
{
  
  std::ostream& 
  operator<<(std::ostream& o, const spec::ModuleSpec& cs);

} // std

#endif // SPEC_MODULE_SPEC_HH
