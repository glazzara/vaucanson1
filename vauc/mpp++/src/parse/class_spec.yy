// -*- C++ -*-
// class_spec.yy
//
//

%{								
#include <string>
#include <iostream>

#include "parse/class_spec_parse.hh"
#include "parse/location.hh"
#include "spec/class_spec.hh"

#define yylex		         	class_spec_lex 
#define yyparse				class_spec_parse
#define YYLSP_NEEDED			1
#define YYDEBUG				0
#define YYERROR_VERBOSE			1
#define yyerror(Msg)			class_parse_error (yylloc, Msg)

#define YYLTYPE				Location

  void class_parse_error (const Location &loc, const char *msg);

  using namespace spec;

  extern ClassSpec*	the_class_spec;
  extern std::ostream	out_stream;	
  extern int		errors;

%}

%pure_parser

%union yystype
{
  int				ival;
  std::string			*str;
  ClassSpec::param_set_t	*param;
  ClassSpec::cpp_param_t	*cpp_param;
  ClassSpec			*class_spec;
}


%token		NAME		"name"
%token		DESCRIPTION	"description"
%token		PARAMETERS	"parameters"	
%token		TYPE		"static type"
%token<str>	ID		"identifier"
%token<str>	DESC		"c++ type description"
%token		COMMA		"comma"

%type<class_spec>		spec 
%type<cpp_param>		param_code
%type<param>			parameters
%type<param>			id_list
%type<str>			code	
%type<str>			description

%start spec

%%
spec:  code NAME ID parameters description TYPE param_code code
{ 
  the_class_spec = new ClassSpec(*$3, *$7, *$4, *$1, *$8, *$5);
  delete $3;
  delete $7;
  delete $4;
  delete $1;
  delete $8;
  delete $5;
}
;

description:
/* empty */		 { $$ = new std::string(); }
| DESCRIPTION code	 { $$ = $2 }
;

parameters: 
  /* empty */            { $$ = new ClassSpec::param_set_t()}
| PARAMETERS id_list     { $$ = $2			    }
;

id_list: 
  ID		         
{ 
  ClassSpec::param_set_t* s = new ClassSpec::param_set_t();
  s->push_back(*$1);
  $$ = s;
}
| ID COMMA id_list	 { $3->push_front(*$1);  $$ = $3      }
;

param_code:	
	DESC             { $$ = new ClassSpec::cpp_param_t(*$1);   }
;

code:
	/* empty */	 { $$ = new std::string; }
|       DESC		 { $$ = $1 } 

%%
void
class_parse_error (const Location &loc, const char *msg)
{
  std::cerr << loc << ": " << msg << std::endl;
  errors++;
}

