/* -*- C -*- */
/* class_spec_scan.ll 
** FIXME : stupid scanner
*/
%{    

#include <string>
#include <errno.h>

#include "spec/class_spec.hh"

  using namespace spec;

#include "parse/class_spec_parse.hh"
#include "parse/class_spec.h"

  // #define YY_NEVER_INTERACTIVE 1
  void 
  class_spec_scan_error(const char* text);


static std::string		current_file;

%}

%option noyywrap
%option nounput
%option outfile="lex.yy.c"
%option prefix="class_spec_"

%x STATE_COMMENT STATE_STRING STATE_DESC

id	[a-zA-Z][a-zA-Z_0-9]*
int	[0-9]+
eol     \n|\r|\n\r|\r\n

%%

"name"		return NAME;
"static type"	return TYPE;
"description"	return DESCRIPTION;
"parameters"	return PARAMETERS;
[ \t]+		yylloc->step ();
{eol}		yylloc->line (yyleng); yylloc->step ();
"//"		BEGIN STATE_COMMENT;
"%{"		yylval->str = new std::string(); BEGIN STATE_DESC;
{id}		yylval->str = new std::string (yytext, yyleng); return ID;
","		return COMMA;
.		class_spec_scan_error(yytext);

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
class_spec_scan_error(const char* text)
{
  std::cerr << "Invalid input :" << text << std::endl;
  exit(EXIT_FAILURE);
}

void
class_spec_scan_open (const std::string &name)
{
  yyin = fopen (name.c_str (), "r");
  current_file = name;

  //  std::cerr << "class specification file : " << name << std::endl;

  if (!yyin)
    {
      std::cerr
	<< "cannot open `" << name << "': " << strerror (errno) << std::endl;
      exit (1);
    }
}

void
class_spec_scan_close (void)
{
  fclose (yyin);
}
