%skeleton "lalr1.cc"
%defines
%define "parser_class_name" "krat_exp_parser"
%error-verbose

%{
# include <vaucanson/algebra/implementation/series/krat_exp_proxy.hh>
# include <map>
# include <queue>
//_DEBUG_
# include <iostream>
%}

%parse-param { std::queue<std::pair<krat_exp_parser::token_type, krat_exp_parser::semantic_type> >& tok_q }
%parse-param { vcsn::algebra::krat_exp_virtual& exp }
%lex-param { std::queue<std::pair<krat_exp_parser::token_type, krat_exp_parser::semantic_type> >& tok_q }

%union
{
  vcsn::algebra::krat_exp_virtual * rexp;
  vcsn::algebra::semiring_virtual * sem;
  std::string * str;
}

%{
int
yylex(yy::krat_exp_parser::semantic_type* yylval,
      std::queue<std::pair<yy::krat_exp_parser::token_type, yy::krat_exp_parser::semantic_type> >& tok_q);
%}

%token	<str> OPAR
%token	<str> CPAR
%token	<str> PLUS
%token	<str> TIMES
%token	<str> STAR
%token	<sem> WEIGHT
%token	<rexp> ONE
%token	<rexp> ZERO
%token	<rexp> WORD
%token  LPROD
%type <rexp> rexp

%left OPAR;
%left PLUS;
%left TIMES;
%left TIMES2;
%left WEIGHT;
%left LPROD;
%left STAR;
%nonassoc ONE;
%nonassoc ZERO;
%nonassoc WORD;

%%
%start exp;

exp :
  rexp {exp = *$1}
  ;

rexp :
    OPAR   rexp   CPAR {$$ = $2}
  | rexp   PLUS   rexp {$$ = *$1 + $3; delete $1; delete $3}
  | rexp   TIMES  rexp {$$ = *$1 * $3; delete $1; delete $3}
  | rexp   rexp	  %prec TIMES2{$$ = *$1 * $2; delete $1; delete $2}
  | rexp   STAR	  {$1->star(); $$ = $1}
  | WEIGHT rexp	  %prec LPROD {$2->left_weight($1); delete $1; $$ = $2}
  | rexp   WEIGHT {$1->right_weight($2); delete $2;$$ = $1}
  | ONE		  {$$ = $1}
  | ZERO	  {$$ = $1}
  | WORD	  {$$ = $1}
  ;

%%

int
yylex(yy::krat_exp_parser::semantic_type* yylval,
      std::queue<std::pair<yy::krat_exp_parser::token_type, yy::krat_exp_parser::semantic_type> >& tok_q)
{
  yy::krat_exp_parser::token_type res;
  if (tok_q.empty())
    return 0;
  else
  {
    *yylval = tok_q.front().second;
    res = tok_q.front().first;
    tok_q.pop();
    return res;
  }
}

void
yy::krat_exp_parser::error(const yy::krat_exp_parser::location_type& loc, const std::string& s)
{
  std::cout << s << std::endl;
}
