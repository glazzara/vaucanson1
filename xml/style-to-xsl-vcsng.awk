BEGIN {
  FS=","
}
/[^,]*,,[^,]*,[^,]*/ {
  print "<xsl:template match=\"@" $1 "\"/>"
  next
}
/[^,]*,[^,]*,[^,]*,[^,]*/ {
  print "<xsl:template match=\"@" $1 "\">"
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
  print "\\providecommand{\\TMP" $1 "}{<xsl:value-of select=\".\"/>}"
  print "\\renewcommand{\\TMP" $1 "}{<xsl:value-of select=\".\"/>}"
  print str
  print "</xsl:template>"
  next
}

