// parse/class_spec_parse.hh
//
//

#ifndef PARSE_CLASS_SPEC_PARSE_HH
# define PARSE_CLASS_PARSE_HH

# include "parse/location.hh"

#define YY_DECL \
  int class_spec_lex (union yystype *yylval, Location *yylloc)
YY_DECL;




#endif // PARSE_CLASS_SPEC_PARSE_HH
