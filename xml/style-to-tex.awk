BEGIN {
  FS=","
}
/[^,]*,[^,]*,[^,]*,[^,]*/ {
  if ($2 == "")
    next
  n = split($2,tab,"#1")
  str = ""
  for (i = 1; i <= n; i++) {
    if (i != 1)
      str = str "\\TMP" $1
    str = str tab[i]
  }
  n = split(str,tab,"$")
  str = tab[1]
  for (i = 1; i <= n; i++) {
    if (i != 1) {
      split(tab[i],var,/[^a-zA-Z]/)
      print "\\providecommand{\\TMP" var[1] "}{}"
      str = str "\\TMP" tab[i]
    }
  }
  print "\\providecommand{\\TMP" $1 "}{" $4 "}"
  print "\\renewcommand{\\TMP" $1 "}{" $4 "}"
  print str "\t%% " $3
  next
}
/% End of LaTeX/{
  exit
}
{
  print
}
