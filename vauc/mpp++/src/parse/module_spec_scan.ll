/* -*- C -*- */
/* module_spec_scan.ll 
** FIXME : stupid scanner
*/
%{    

#include <string>
#include <errno.h>

#include "spec/module_spec.hh"
#include "parse/module_spec_parse.hh"
  
using namespace spec;

#include "parse/module_spec.h"

static std::string		current_file;

%}

%option noyywrap
%option nounput
%option outfile="lex.yy.c"
%option prefix="module_spec_"

%x STATE_COMMENT STATE_DESC

id	[a-zA-Z][a-zA-Z_0-9.]*
int	[0-9]+
eol     \n|\r|\n\r|\r\n

%%

"description"	return DESCRIPTION;
"name"		return NAME;
"alias"		return ALIAS;
"type"		return TYPE;
"object"	return OBJECT;
"fun"		return FUN;
"is"		return IS;
"("		return LPAREN;
")"		return RPAREN;
":"		return COLON;
","		return COMMA;
"->"		return ARROW;
"="		return EQ;
"with"		return WITH;
[ \t]+		yylloc->step ();
{eol}		yylloc->line (yyleng); yylloc->step ();
"%{"		yylval->str = new std::string (); BEGIN STATE_DESC;
"//"		BEGIN STATE_COMMENT;
{id}		{
  yylval->str = new std::string(); 
  yylval->str->append(yytext, yyleng); 
  return ID;
}
.		{ std::cerr << "scanner : Invalid input : " << yytext << std::endl; }

<STATE_DESC>
{
  "%}"	    {
    BEGIN INITIAL;
    return DESC;
  }

  .|\n      yylloc->line(); yylval->str->append (yytext, yyleng);

     <<EOF>> {
       /* FIXME : ERROR */
       BEGIN INITIAL;
       return DESC;
     }

}

<STATE_COMMENT>
{
  "\n"	    yylloc->line(); BEGIN INITIAL;
  .	    /* eat */
}


%%

void
module_spec_scan_open (const std::string &name)
{
  yyin = fopen (name.c_str (), "r");
  current_file = name;

  std::cerr << "module specification file : " << name << std::endl;

  if (!yyin)
    {
      std::cerr
	<< "cannot open `" << name << "': " << strerror (errno) << std::endl;
      exit (1);
    }
}

void
module_spec_scan_close (void)
{
  fclose (yyin);
}
