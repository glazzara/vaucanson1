#!/bin/sh
# in2grammar.sh: parser generator for libcppshls
# Written by Raphaël Poss <raph@lrde.epita.fr>
# Copyright (c) 2002 LRDE.

if [ $# -lt 1 ]; then
  echo "usage: $0 <mode>" >&2
  echo "  <mode> : 'yy', 'y' or 'lemon'" >&2
  exit 1
fi

if [ "x$1" != xy -a "x$1" != xyy -a "x$1" != xlemon ]; then
  echo "invalid mode" >&2
  exit 1
fi

if [ $1 = lemon ]; then
sed_script=`cat <<EOF
s,//only lemon.*,,g
s,^.*//only bison.*,,g
s,"->",RARROW,g
s,"<-",LARROW,g
s,":=",BIND,g
s,"<<",IOIN,g
s,">>",IOOUT,g
s,"in",IN,g
s,"with",WITH,g
s,"begin",BEGIN,g
s,"end",END,g
s,"elif",ELIF,g
s,"try",TRY,g
s,"fun",FUN,g
s,"foreach",FOREACH,g
s,"for",FOR,g
s,"let",LET,g
s,"if",IF,g
s,"do",DO,g
s,"to",TO,g
s,"or",TO,g
s,"downto",DOWNTO,g
s,"then",THEN,g
s,"else",ELSE,g
s,"and",AND,g
s,"while",WHILE,g
s,"++",INCR,g
s,"--",DECR,g
s,"<>",DIFFERENT,g
s,"<=",LE,g
s,">=",GE,g
s,"==",EQ,g
s,"\.=",IN_DOT,g
s,"!=",NE,g
s,"//",NS,g
s,"\.\.",DDOT,g
s,"::",CONS,g
s,"||",LOR,g
s,"&&",LAND,g
s,"^^",LXOR,g
s,"!!",IN_NOT,g
s,"+=",IN_PLUS,g
s,"!-",IN_MINUS,g
s,"!\.",IN_DOT,g
s,"!/",IN_DIV,g
s,"!*",IN_STAR,g
s,"!&&",IN_LAND,g
s,"!||",IN_LOR,g
s,"!^^",IN_LXOR,g
s.'@'.CAT.g
s.','.COMMA.g
s,'!',NOT,g
s,'|',BAR,g
s,'\*',STAR,g
s,'=',EQUAL,g
s,'<',LT,g
s,'>',GT,g
s,';',SEMICOLON,g
s,'^',IN_STAR,g
s,'[$]',DOLLAR,g
s,':',COLON,g
s,'+',PLUS,g
s,'-',MINUS,g
s,'\.',DOT,g
s,'/',DIV,g
s,'(',LPAREN,g
s,')',RPAREN,g
s,'\[',LBRACKET,g
s,'\]',RBRACKET,g
s,'{',LBRACE,g
s,'}',RBRACE,g
s,\%prec \([A-Z_]*\) *;,. [\1],g
s,^\([a-z_]*\) :,\1(RX) ::=,g
s,; *$,.,g
s,[$][$],RX,g
s,[$]\([0-9]\),IN_DEBUG(X\1),g
s,%%,,g
s,%left .*,& .,g
s,%right .*,& .,g
s,%nonassoc .*,& .,g
EOF
`
else
sed_script=`cat <<EOF
s,^.*//only lemon.*,,g
s,//only bison.*,,g
s,\(^[a-z_]* *:.*\); *$,\1,g
s,^{.*} *$,& ;,g
s,(X[0-9]),,g
s,[$][0-9],IN_DEBUG(&),g
s,\\\\\\\\$,,g
EOF
`
fi

if [ $1 = lemon ]; then
  sed -e 's,%,%%,g;s,\@,%x,g' \
    | tr '\n' '@' \
    | sed -e 's,\\\@,,g' \
    | tr '@' '\n' \
    | sed -e 's,%x,\@,g;s,%%,%,g'
else
  cat
fi | sed -e "$sed_script"

