#ifndef Y_TAB_H
# define Y_TAB_H

typedef union yystype
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

} YYSTYPE;
# define	ALIAS	257
# define	NAME	258
# define	TYPE	259
# define	FUN	260
# define	IS	261
# define	LPAREN	262
# define	RPAREN	263
# define	ARROW	264
# define	COMMA	265
# define	DESCRIPTION	266
# define	COLON	267
# define	EQ	268
# define	WITH	269
# define	ID	270
# define	DESC	271
# define	OBJECT	272


#endif /* not Y_TAB_H */
