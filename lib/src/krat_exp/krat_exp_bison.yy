%require "2.5"
%skeleton "lalr1.cc"
%defines
%define "parser_class_name" "krat_exp_bison"
%locations
//%debug
%error-verbose
%name-prefix="vcsnyy"

%code requires
{
# include <vaucanson/algebra/implementation/series/krat_exp_parser_private.hh>
# include <map>
# include <queue>
# include <string>
# include <cassert>
//_DEBUG_
# include <iostream>
}

%code
{
  namespace vcsnyy
  {
    typedef std::pair<krat_exp_bison::token_type,
                      krat_exp_bison::semantic_type>
      token_t;
    typedef std::queue<token_t > tokens_t;
  }

  int
  yylex(vcsnyy::krat_exp_bison::semantic_type* yylval,
        vcsnyy::krat_exp_bison::location_type* yylloc,
        vcsnyy::tokens_t& tok_q);
}

%parse-param { std::queue<std::pair<krat_exp_bison::token_type, krat_exp_bison::semantic_type> >& tok_q }
%parse-param { vcsn::algebra::krat_exp_virtual& exp }
%parse-param { std::string& error_ }
%lex-param   { tokens_t& tok_q }

%printer { debug_stream() << *$$; } <str>

%union
{
  vcsn::algebra::krat_exp_virtual * rexp;
  vcsn::algebra::semiring_virtual * sem;
  std::string * str;
}

%type <rexp> rexp

%token <str> OPAR CPAR
%left <str> PLUS
%left <str> TIMES
%left TIMES2
%left <sem> WEIGHT
%left LPROD
%left <str> STAR
%nonassoc <rexp> ZERO
%nonassoc <rexp> WORD

%%
%start exp;

exp :
  rexp {exp = *$1; delete $1; }
  ;

rexp :
    OPAR   rexp   CPAR {$$ = $2 ; delete $1; delete $3;}
  | rexp   PLUS   rexp {$$ = *$1 + $3; delete $1; delete $2; delete $3;}
  | rexp   TIMES  rexp {$$ = *$1 * $3; delete $1; delete $2; delete $3;}
  | rexp   rexp	  %prec TIMES2{$$ = *$1 * $2; delete $1; delete $2;}
  | rexp   STAR	  {$1->star(); $$ = $1; delete $2;}
  | WEIGHT rexp	  %prec LPROD {$2->left_weight($1); delete $1; $$ = $2;}
  | rexp   WEIGHT {$1->right_weight($2); delete $2;$$ = $1;}
  | ZERO	  {$$ = $1;}
  | WORD	  {$$ = $1;}
  ;

%%

namespace vcsnyy
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

  krat_exp_parser::krat_exp_parser()
  {
    tok_q_ = new token_queue;
  }

  krat_exp_parser::~krat_exp_parser()
  {
    delete tok_q_;
  }

  void
  krat_exp_parser::insert_word(vcsn::algebra::krat_exp_virtual* rexp)
  {
    krat_exp_bison::semantic_type tmp;
    tmp.rexp = rexp;
    tok_q_->self.push(std::make_pair(krat_exp_bison::token::WORD, tmp));
  }

  void
  krat_exp_parser::insert_weight(vcsn::algebra::semiring_virtual* sem)
  {
    krat_exp_bison::semantic_type tmp;
    tmp.sem = sem;
    tok_q_->self.push(std::make_pair(krat_exp_bison::token::WEIGHT, tmp));
  }

  void
  krat_exp_parser::insert_zero(vcsn::algebra::krat_exp_virtual* rexp)
  {
    krat_exp_bison::semantic_type tmp;
    tmp.rexp = rexp;
    tok_q_->self.push(std::make_pair(krat_exp_bison::token::ZERO, tmp));
  }

  void
  krat_exp_parser::insert_token(int i, std::string* str)
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
      default : // this step should never append
        assert(false);
        break;
      }
  }

  int
  krat_exp_parser::parse(vcsn::algebra::krat_exp_virtual& rexp_,
                         std::string& error_)
  {
    krat_exp_bison parser(tok_q_->self , rexp_, error_);
  #if YYDEBUG
    parser.set_debug_level(true);
  #endif
    return parser.parse();
  }

  void
  krat_exp_bison::error(const krat_exp_bison::location_type& loc,
                        const std::string& s)
  {
    error_ += s + '\n';
  }

} // namespace vcsnyy


int
vcsnyylex(vcsnyy::krat_exp_bison::semantic_type* yylval,
          vcsnyy::krat_exp_bison::location_type*,
          vcsnyy::tokens_t& tok_q)
{
  vcsnyy::krat_exp_bison::token_type res;
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


// Local Variables:
// mode: c++
// End:
