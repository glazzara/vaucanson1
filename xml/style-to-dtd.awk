BEGIN {
  FS=","
  print "<!ATTLIST geometry"
}
/[^,]*,[^,]*,[^,]*,[^,]*/ {
  if ($4 ~ /</) {
    split($4, tab, "<")
    first = 1
    str = ""
    for (i in tab) {
      if (first)
        first = 0
      else
        str = str "&lt;"
      str = str tab[i]
    }
  }
  else
    str = $4
  if (str == "")
    print  $1 " CDATA #IMPLIED"
  else if ($3 ~ /\(.*\)/)
    print $1 " " $3 " \"" str "\""
  else
    print $1 " CDATA \"" str "\""
}
END {
  print ">"
}
