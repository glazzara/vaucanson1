#ifndef Y_TAB_H
# define Y_TAB_H

typedef union yystype
{
  int				ival;
  std::string			*str;
  ClassSpec::param_set_t	*param;
  ClassSpec::cpp_param_t	*cpp_param;
  ClassSpec			*class_spec;
} YYSTYPE;
# define	NAME	257
# define	DESCRIPTION	258
# define	PARAMETERS	259
# define	TYPE	260
# define	ID	261
# define	DESC	262
# define	COMMA	263


#endif /* not Y_TAB_H */
