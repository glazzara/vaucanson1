// -*- C++ -*-
// fun_spec.yy
//
//

%{								
#include <string>
#include <iostream>

#include "parse/fun_spec_parse.hh"
#include "parse/location.hh"
#include "spec/fun_spec.hh"

#define yylex		         	fun_spec_lex 
#define yyparse				fun_spec_parse
#define YYLSP_NEEDED			1
#define YYDEBUG				1
#define YYERROR_VERBOSE			1
#define yyerror(Msg)			fun_parse_error (yylloc, Msg)

#define YYLTYPE				Location

  using namespace spec;

  void fun_parse_error (const Location &loc, const char *msg);

  extern FunSpec*	the_fun_spec;
  extern std::ostream	out_stream;	
  extern int		errors;

%}

%pure_parser

%union yystype
{
  int				ival;
  std::string			*str;
  spec::FunSpec			*fun_spec;
  spec::FunSig			*fun_sig;
  std::list<spec::FunSig>	*fun_sigs;
  FunSpec::param_set_t		*param_set;
}

%left ARROW
%left COLON

%token		NAME		"name"
%token		PARAMETERS	"parameters"
%token		ARROW		"->"
%token		COMMA		","
%token		DESCRIPTION	""
%token		COLON		":"
%token<str>	ID		"identifier"
%token<str>	DESC		"description"


%type<fun_spec>		spec 
%type<str>		code
%type<fun_sigs>		fun_versions
%type<fun_sig>		fun_version
%type<fun_sig>		signature
%type<param_set>	parameters
%type<str>		description
%type<param_set>	id_list

%start spec

%%
spec:   code NAME ID description parameters fun_versions code
{
  the_fun_spec = new FunSpec(*$3, *$6, *$5, *$1, *$7, *$4);   
  delete $3;
  delete $5;
  delete $1;
  delete $7;
  delete $6;
  $$ = the_fun_spec;
}
;

description:
/* empty */		 { $$ = new std::string(); }
| DESCRIPTION code	 { $$ = $2                 }
;

parameters: 
  /* empty */            { $$ = new FunSpec::param_set_t()}
| PARAMETERS id_list     { $$ = $2			    }
;

id_list: 
  ID		         
{ 
  FunSpec::param_set_t* s = new FunSpec::param_set_t();
  s->push_back(*$1);
  $$ = s;
}
| ID COMMA id_list	 { $3->push_front(*$1);  $$ = $3      }
;


fun_versions: fun_version
{
  std::list<FunSig>   *sigs = new std::list<FunSig>();
  sigs->push_back(*$1);
  delete($1);
  $$ = sigs;
}
| fun_versions fun_version
{
  $1->push_back(*$2);
  delete($2);
  $$ = $1;
}
;

fun_version: signature DESC
{ 
  $1->call = *$2;
  delete $2;
  $$ = $1;
}
;

signature: 
  ID 
{ 
  FunSpec::signature_t* sig = new FunSpec::signature_t();
  sig->args.push_back(std::make_pair("ret", *$1));
  $$ = sig
}
| ID COLON ID ARROW signature
{
  $5->args.push_front(std::make_pair(*$1 , *$3));
  $$ = $5;
}
;

code:	/* empty */ { $$ = new std::string(); }
|	DESC        { $$ = $1;  }
;

%%
void
fun_parse_error (const Location &loc, const char *msg)
{
  std::cerr << loc << ": " << msg << std::endl;
  errors++;
}

