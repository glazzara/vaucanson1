#ifndef Y_TAB_H
# define Y_TAB_H

typedef union yystype
{
  int				ival;
  std::string			*str;
  spec::FunSpec			*fun_spec;
  spec::FunSig			*fun_sig;
  std::list<spec::FunSig>	*fun_sigs;
  FunSpec::param_set_t		*param_set;
} YYSTYPE;
# define	NAME	257
# define	PARAMETERS	258
# define	ARROW	259
# define	COMMA	260
# define	DESCRIPTION	261
# define	COLON	262
# define	ID	263
# define	DESC	264


#endif /* not Y_TAB_H */
