// parse/fun_spec_parse.hh
//
//

#ifndef PARSE_FUN_SPEC_PARSE_HH
# define PARSE_FUN_PARSE_HH

# include "parse/location.hh"

#define YY_DECL \
  int fun_spec_lex (union yystype *yylval, Location *yylloc)
YY_DECL;




#endif // PARSE_FUN_SPEC_PARSE_HH
