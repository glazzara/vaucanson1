// -*- C++ -*-
// module_spec.yy
//
//

%{								
#include <string>
#include <iostream>

#include "parse/module_spec_parse.hh"
#include "parse/location.hh"
#include "spec/module_spec.hh"

#define yylex		         	module_spec_lex 
#define yyparse				module_spec_parse
#define YYLSP_NEEDED			1
#define YYDEBUG				0
#define YYERROR_VERBOSE			1
#define yyerror(Msg)			module_parse_error (yylloc, Msg)

#define YYLTYPE				Location

  using namespace spec;

  void module_parse_error (const Location &loc, const char *msg);

  extern ModuleSpec*	the_module_spec;
  extern std::ostream	out_stream;	
  extern int		errors;

%}

%pure_parser

%union yystype
{
  int					ival;
  std::string				*str;
  spec::ModuleSpec			*module_spec;
  spec::ModuleSpec::param_set_t		*param_set;
  spec::Version				*version;
  std::list<spec::Version*>		*list_version;
  spec::FunVersion::sigs_t		*signatures;
  std::list<std::string>		*signature;
  spec::ModuleSpec::param_value_t	*args;

}


%token		ALIAS		
%token		NAME		
%token		TYPE		
%token		FUN		
%token		IS		
%token		LPAREN		
%token		RPAREN		
%token		ARROW		
%token		COMMA		
%token		DESCRIPTION
%token		COLON		
%token		EQ		
%token		WITH		
%token<str>	ID		
%token<str>	DESC		
%token		OBJECT		


%type<module_spec>		spec 
%type<str>			code
%type<list_version>		dec_list
%type<version>			dec 
%type<str>			description
%type<version>			type_dec
%type<version>			function_dec
%type<version>			object_dec
%type<version>			alias_dec
%type<signature>		signature
%type<signatures>		restriction
%type<signatures>		fun_versions
%type<args>			args
%type<args>			args_list


%start spec

%%
spec:   code NAME ID description dec_list
{
  // FIXME ... it's "gore"
  std::list<FunVersion>			  funs;
  std::list<TypeVersion>		  types;
  std::list<ObjectVersion>	         objects;
  std::map<std::string, std::string>	  aliases;

  for (std::list<Version*>::const_iterator v = $5->begin();
       v != $5->end();
       ++v)
    {
      Version *v_ = *v;
      FunVersion * f = dynamic_cast<FunVersion*>((v_));
      if (f != 0)
	{
	  funs.push_back(*f);
	  std::cerr << "function : " << (*f).name << std::endl;
	  continue;
	}
      TypeVersion* t = dynamic_cast<TypeVersion*>((v_));
      if (t != 0)
	{
	  types.push_back(*t);
	  std::cerr << "type : " << (*t).name << std::endl;
	  continue;
	}
      ObjectVersion* o = dynamic_cast<ObjectVersion*>((v_));
      if (o != 0)
	{
	  objects.push_back(*o);
	  std::cerr << "object : " << (*o).name << std::endl;
	  continue;
	}
      Alias* a = dynamic_cast<Alias*>((v_));
      if (a != 0)
	{
	  if (aliases.find(a->alias) != aliases.end())
	    {
	      std::cerr << "This alias is multiply defined : " << a->alias << std::endl;
	      exit(EXIT_FAILURE);
	    }
	  aliases[a->alias] = a->realname;
	  std::cerr << "alias : " << (*a).alias << std::endl;
	  continue;
	}
      std::cerr << "Fatal error : expecting a Type or a Function. Got 'something else'" 
		<< std::endl;
      exit(EXIT_FAILURE);
    }
  the_module_spec = new ModuleSpec(*$3, funs, types, objects, aliases, *$1, *$4); 
  delete($4);
  $$ = the_module_spec;
}
;

description:
/* empty */		 { $$ = new std::string(); }
| DESCRIPTION code	 { $$ = $2 }
;

dec_list : 
/* empty */		{ $$ = new std::list<Version*> ; }
| dec_list dec          { $1->push_back($2); $$ = $1;   }
;

dec :
type_dec			{ $$ = $1 }
| function_dec			{ $$ = $1 }
| object_dec			{ $$ = $1 }
| alias_dec			{ $$ = $1 }
;

object_dec:
OBJECT ID COLON ID DESC
{
  ObjectVersion* o = new ObjectVersion();
  o->name = *$2;
  o->dynamic_type = *$4;
  o->value        = *$5;
  $$ = o
}

alias_dec:
ALIAS ID IS ID
{
  Alias* a      = new Alias();
  a->alias      = *$2;
  a->realname  = *$4;
  $$ = a;
}

type_dec:
TYPE ID			
{ 
  TypeVersion* t = new TypeVersion();
  t->name = *$2;
  $$ = t;
}
| TYPE ID IS ID args      	
{
  TypeVersion* t = new TypeVersion();
  t->dynamic_name    = *$2;
  t->name	 = *$4;
  t->args	 = *$5;
  $$		 = t;
}
;

args:
/* empty */                     { $$ = new spec::ModuleSpec::param_value_t(); }
| WITH args_list		{ $$ = $2; }
;

args_list:
ID EQ ID			
{
  spec::ModuleSpec::param_value_t*  p = new spec::ModuleSpec::param_value_t();
  (*p)[*$1] = *$3;
  $$ = p;
}
| args_list COMMA ID EQ ID	
{ 
  (*$1)[*$3] = *$5; 
  $$ = $1; 
}
;

function_dec: 
FUN ID IS ID args restriction 
{
  FunVersion* f   = new FunVersion();
  f->dynamic_name = *$2;
  f->name	  = *$4;
  f->args	  = *$5;
  f->sigs	  = *$6;
  $$ = f;
}
;

restriction:
/* empty */			
{
  $$ = new FunVersion::sigs_t();
}
| COLON fun_versions			
{
  $$ = $2
}
;

fun_versions: signature
{
  FunVersion::sigs_t   *sigs = new FunVersion::sigs_t();
  sigs->push_back(*$1);
  delete($1);
  $$ = sigs;
}
| fun_versions signature
{
  $1->push_back(*$2);
  delete($2);
  $$ = $1;
}
;

signature: 
  ID 
{ 
  FunVersion::signature_t* sig = new FunVersion::signature_t();
  sig->push_back(*$1);
  $$ = sig
}
| signature ARROW ID
{
  $1->push_back(*$3);
  $$ = $1;
}
;

code:	/* empty */ { $$ = new std::string(); }
|	DESC        { $$ = $1;  }
;

%%
void
module_parse_error (const Location &loc, const char *msg)
{
  std::cerr << loc << ": " << msg << std::endl;
  errors++;
}

