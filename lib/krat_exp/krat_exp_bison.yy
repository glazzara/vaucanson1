%skeleton "lalr1.cc"
%defines
%define "parser_class_name" "krat_exp_bison"
%error-verbose

%{
# include <vaucanson/algebra/implementation/series/krat_exp_proxy.hh>
# include <map>
# include <queue>
# include <string>
//_DEBUG_
# include <iostream>
%}

%parse-param { std::queue<std::pair<krat_exp_bison::token_type, krat_exp_bison::semantic_type> >& tok_q }
%parse-param { vcsn::algebra::krat_exp_virtual& exp }
%parse-param { std::string& error_ }
%lex-param { std::queue<std::pair<krat_exp_bison::token_type, krat_exp_bison::semantic_type> >& tok_q }

%union
{
  vcsn::algebra::krat_exp_virtual * rexp;
  vcsn::algebra::semiring_virtual * sem;
  std::string * str;
}

%{
int
yylex(yy::krat_exp_bison::semantic_type* yylval,
      std::queue<std::pair<yy::krat_exp_bison::token_type, yy::krat_exp_bison::semantic_type> >& tok_q);
%}

%token	<str> OPAR
%token	<str> CPAR
%token	<str> PLUS
%token	<str> TIMES
%token	<str> STAR
%token	<sem> WEIGHT
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
%nonassoc ZERO;
%nonassoc WORD;

%%
%start exp;

exp :
  rexp {exp = *$1; delete $1}
  ;

rexp :
    OPAR   rexp   CPAR {$$ = $2 ; delete $1; delete $3}
  | rexp   PLUS   rexp {$$ = *$1 + $3; delete $1; delete $2; delete $3}
  | rexp   TIMES  rexp {$$ = *$1 * $3; delete $1; delete $2; delete $3}
  | rexp   rexp	  %prec TIMES2{$$ = *$1 * $2; delete $1; delete $2}
  | rexp   STAR	  {$1->star(); $$ = $1; delete $2}
  | WEIGHT rexp	  %prec LPROD {$2->left_weight($1); delete $1; $$ = $2}
  | rexp   WEIGHT {$1->right_weight($2); delete $2;$$ = $1}
  | ZERO	  {$$ = $1}
  | WORD	  {$$ = $1}
  ;

%%

namespace yy
{
  struct token_queue
  {
    std::queue
    <
      std::pair
      <
	krat_exp_bison::token_type,
	krat_exp_bison::semantic_type
      >
    > self;
  };

  // WARNING: this struct declaration is also in
  //   include/vaucanson/algebra/implementation/series/krat_exp_parser.hxx
  // until someone factors these, you have to update both.
  struct krat_exp_parser
  {
    krat_exp_parser();
    ~krat_exp_parser();
    void insert_word(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_weight(vcsn::algebra::semiring_virtual* sem);
    void insert_zero(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_token(int i, std::string* str);
    int parse(vcsn::algebra::krat_exp_virtual& rexp, std::string& error);

    // Attributs
    token_queue* tok_q_;
  }; // krat_exp_parser
} // yy

yy::krat_exp_parser::krat_exp_parser()
{
  tok_q_ = new token_queue;
}

yy::krat_exp_parser::~krat_exp_parser()
{
  delete tok_q_;
}

void
yy::krat_exp_parser::insert_word(vcsn::algebra::krat_exp_virtual* rexp)
{
  krat_exp_bison::semantic_type tmp;
  tmp.rexp = rexp;
  tok_q_->self.push(std::make_pair(krat_exp_bison::token::WORD, tmp));
}

void
yy::krat_exp_parser::insert_weight(vcsn::algebra::semiring_virtual* sem)
{
  krat_exp_bison::semantic_type tmp;
  tmp.sem = sem;
  tok_q_->self.push(std::make_pair(krat_exp_bison::token::WEIGHT, tmp));
}

void
yy::krat_exp_parser::insert_zero(vcsn::algebra::krat_exp_virtual* rexp)
{
  krat_exp_bison::semantic_type tmp;
  tmp.rexp = rexp;
  tok_q_->self.push(std::make_pair(krat_exp_bison::token::ZERO, tmp));
}

void
yy::krat_exp_parser::insert_token(int i, std::string* str)
{
  krat_exp_bison::semantic_type tmp;
  tmp.str = str;
  switch (i)
  {
    case 0 :
      tok_q_->self.push(std::make_pair(krat_exp_bison::token::OPAR, tmp));
      break;
    case 1 :
      tok_q_->self.push(std::make_pair(krat_exp_bison::token::CPAR, tmp));
      break;
    case 2 :
      tok_q_->self.push(std::make_pair(krat_exp_bison::token::PLUS, tmp));
      break;
    case 3 :
      tok_q_->self.push(std::make_pair(krat_exp_bison::token::TIMES, tmp));
      break;
    case 4 :
      tok_q_->self.push(std::make_pair(krat_exp_bison::token::STAR, tmp));
      break;
    default : // this sted should never append
      std::cout << "Error in insert_token" << std::endl;
      break;
  }
}

int
yy::krat_exp_parser::parse(vcsn::algebra::krat_exp_virtual& rexp_, std::string& error_)
{
  yy::krat_exp_bison parser(tok_q_->self , rexp_, error_);
  return parser.parse();
}

int
yylex(yy::krat_exp_bison::semantic_type* yylval,
      std::queue<std::pair<yy::krat_exp_bison::token_type, yy::krat_exp_bison::semantic_type> >& tok_q)
{
  yy::krat_exp_bison::token_type res;
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
yy::krat_exp_bison::error(const yy::krat_exp_bison::location_type& loc, const std::string& s)
{
  error_ += s + '\n';
}
