BEGIN {
  FS=","
  code = ""
  strs = ""
}
/[^,]*,[^,]*,[^,]*,[^,]*/ {
  strs = strs "//str_" $1 " \n"
  if (($3 == "int") || ($3 == "float"))
    code = code "\n  SET_ATTR(g, " $1 ");"
  else if ($3 ~ /\(.*\)/) {
    code = code "\n\n  OPTION_ATTR(g, " $1 ",\n"
    split($3,p,/\(|\)/)
    split(p[2],tab,"|")
    first = 1
    for (i in tab) {
      if (first)
        first = 0
      else
        code = code "\n    else\n"
      code = code "    OPTION(g, " $1 ", GeometryValue::V_" tab[i] ", " tab[i] ")"
      strs = strs "//str_" tab[i] " \n"
    }
    code = code ");\n"
  }
  else
    code = code "\n  SET_ATTR(g, " $1 ");"
}
END {
  print code
  print strs
}
