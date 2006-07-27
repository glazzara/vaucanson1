#! /bin/sh

generate_one_section ()
{
  local kind=$1
  local short=$2
  local vcsn=vcsn-$short

  echo "\\section{$kind"}

  $vcsn list-automata |
    sed -n 's/ *- *//p' |
    while read a
    do
      cat <<EOF
\\subsection{$a}
\\label{$short:$a}
\\execdisplay{al-$short-$a}{$vcsn dump-automaton $a | $vcsn}{-}

EOF
    done
}


cat <<'EOF'
% Generated, do not edit by hand.
\chapter{Automaton Library}

\Vauc comes with a set of interesting automata that can be used to toy
with \tafkit (\autoref{sec:tafkit}) for instance.  In the chapter, we
present each one of these automata.


EOF
generate_one_section 'Boolean Automata'     b
generate_one_section '\texorpdfstring{$\mathbb{Z}$}{Z}-Automata'  z
generate_one_section 'Transducers'          tdc
