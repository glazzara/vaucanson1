BEGIN {
  FS=","
  enums = "{"
  vars = ""
}
/[^,]*,[^,]*,[^,]*,[^,]*/ {
  if (($3 == "int") || ($3 == "float"))
    vars = vars "\n" "  Optionnal<" $3 "> " $1 ";"
  else if ($3 ~ /\(.*\)/) {
    enum = "enum { "
    split($3,p,/\(|\)/)
    split(p[2],tab,"|")
    first = 1
    for (i in tab) {
      if (first)
        first = 0
      else
        enum = enum ", "
      enum = enum "V_" tab[i]
    }
    enum = enum " };"
    if (!index(enums, enum))
      enums = enums "\n  " enum
    vars = vars "\n" "  Optionnal<int> " $1 ";"
  }
  else if ($3 == "bool")
    vars = vars "\n" "  Optionnal<bool> " $1 ";"
  else
    vars = vars "\n" "  Optionnal<std::string> " $1 ";"
}
END {
  print "struct GeometryValue"
  print enums
  print vars
  print "};"
}
