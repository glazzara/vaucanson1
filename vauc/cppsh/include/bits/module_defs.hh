
#ifndef CPPSH_BITS_MODULE_DEFS_HH
#define CPPSH_BITS_MODULE_DEFS_HH

#include "kern/object.hh"
#include "env/call_env_base.hh"

namespace cppsh
{
  namespace bits
  {
    struct component
    { 
      enum kind
	{ 
	  empty = 0, 
	  typeinfo, 
	  fun, 
	  obj,
	  cons,
	  cast_op,
	  alias,
	  deftab = 100, 
	  deftab_gen
	};
    };

    struct definition
    {
      component::kind  def_kind;
      const component* piece;
    };

    struct definition_table : component
    {
      const definition* array;
    };

    struct definition_table_gen : component
    {
      const definition* (*gen)();
    };

    /* type information: link a mangled name to useful information */
    struct typeinfo_spec : component
    {
      const std::type_info* type_info;
      /* key name for the type. most useful values are short names,
         but can be set to the type_info.name(). */
      const char* key;
      /* set the description to 0 if not available */
      const char* description;
    };

    /* function signature: clear names of return and arguments types */
    struct fun_sig_spec
    {
      /* if ret_type is set to 0 the function returns no value. */
      /* if ret_type is set to the empty string, expect any return type */
      const char*  ret_type;
      /* if arg_types is set to 0, the function as a vararg signature. */
      /* if any arg_types element is set to the empty string (""), 
         the corresponding argument can be of any type. */
      /* the arg_types array is 0-terminated. */
      const char** arg_types;
    };

    typedef Object (*dfun_ptr)(void*, const CallEnvBase&, size_t argc, const Object argv[]);

    /* function information: link a function pointer to useful information. */
    struct fun_spec : component
    {
      /* the function pointer. */
      dfun_ptr      fptr;
      /* the function's exact signature. May not be empty. */
      fu_sig_spec*  signature;
      /* the function's "visible" signature. May be empty. */
      fun_sig_spec* visible_signature;
      /* the function name. several functions can have the same name. */
      const char*  name;
      /* the function description. may be set 0 if not available. */
      const char*  description;
      /* private data for use by the function */
      void*      f_dptr;
    };

    /* constant information: link a generator function to useful information. */
    typedef Object (*dgen_ptr)(void *, const CallEnvBase&);
    struct obj_spec : component
    {
      /* the generator pointer */
      dgen_ptr     fptr;
      /* the name of the constant. */
      const char*  name;
      /* private data for use by the function */
      void*      f_dptr;
    };


    /*---------------------.
    | less-used constructs |
    `---------------------*/

    /* constructor information: link a function to a type */
    struct cons_spec : component
    {
      /* the name of the type receiving a constructor */
      const char*  type_name;
      /* the name of the target function for the construction */
      const char*  cons_name;
    };
      
    /* reference cast: identity functions which only change the type_info */
    typedef Object (*dcast_op_ptr)(Object);
    struct cast_op_spec : component
    {
      /* the cast pointer */
      dcast_op_ptr op;
      /* the source mangled name */
      const char*  src_name;
      /* the destination mangled name */
      const char*  dst_name;
      /* the direction of the cast: up is transparent, down uses dynamic_cast */
      enum direction_t { upcast, downcast } direction;
    };

    /* alias specification: link a name to another */
    struct alias_spec : component
    {
      /* the name of the link */
      const char*   link_name;
      /* the name of the target of the link */
      const char*   target_name;
    };


  }
}

#endif
