#ifndef CPPSH_BITS_DEF_VISITOR_HH
#define CPPSH_BITS_DEF_VISITOR_HH

#include "bits/module_defs.hh"

namespace cppsh
{
  namespace bits
  {
    template<typename Client>
    void visit_definition(Client& c, const definition& d, bool recursive)
    {
      switch(d.def_kind)
	{
	case empty: 
	  return;
	case typeinfo: 
	  return (void)c.register_typeinfo(static_cast<const typeinfo_spec&>(*d.piece));
	case fun:
	  return (void)c.register_function(static_cast<const fun_spec&>(*d.piece));
	case obj:
	  return (void)c.register_constant(static_cast<const obj_spec&>(*d.piece));
	case cons:
	  return (void)c.register_constructor(static_cast<const cons_spec&>(*d.piece));
	case cast_op:
	  return (void)c.register_cast_op(static_cast<const cast_op_spec&>(*d.piece));
	case deftab:
	case deftab_gen:
	  if (recursive)
	    {
	      const definition* p;
	      if (d.def_kind == deftab)
		p = static_cast<const definition_table*>(d.piece)->array;
	      else
		p = static_cast<const definition_table_gen*>(d.piece)->gen();

	      for ( ; p->def_kind != empty; ++p)
		visit_definition(c, *p, recursive);
	    }
	  return;
	default:
	  return (void)c.visit_unknown(d);
	}
    }
		
	  

  }
}


#endif
