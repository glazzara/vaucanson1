// parse/module_spec_parse.hh
//
//

#ifndef PARSE_MODULE_SPEC_PARSE_HH
# define PARSE_MODULE_PARSE_HH

# include "parse/location.hh"

#define YY_DECL \
  int module_spec_lex (union yystype *yylval, Location *yylloc)
YY_DECL;




#endif // PARSE_MODULE_SPEC_PARSE_HH
