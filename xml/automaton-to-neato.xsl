<?xml version="1.0" encoding="iso8859-1" ?>
<!DOCTYPE stylesheet>
<xsl:transform version="1.0"
	       exclude-result-prefixes="vcsn"
               xmlns:vcsn="http://www.lrde.epita.fr/vaucanson"
               xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text"
               encoding="iso8859-1"/>

  <xsl:template match="/">digraph vcsn {
  label="automaton";
   <xsl:apply-templates select="//vcsn:structure"/>
}
  </xsl:template>

  <xsl:template match="vcsn:structure">
    <xsl:apply-templates select="//vcsn:state"/>
    <xsl:apply-templates select="//vcsn:edge"/>
    <xsl:apply-templates select="//vcsn:initial"/>
    <xsl:apply-templates select="//vcsn:final"/>
  </xsl:template>

  <xsl:template match="vcsn:initial">
    <xsl:value-of select="@state"/>_invisible_in
 	[style=invis,label="",width=.01,height=.01];
    <xsl:value-of select="@state"/>_invisible_in
	-> <xsl:value-of select="@state"/>
	   [label="<xsl:value-of select="@label"/>"];
  </xsl:template>

  <xsl:template match="vcsn:final">
    <xsl:value-of select="@state"/>_invisible_out
	[style=invis,label="",width=.01,height=.01];
    <xsl:value-of select="@state"/>
	-> <xsl:value-of select="@state"/>_invisible_out
	   [label="<xsl:value-of select="@label"/>"];
  </xsl:template>

  <xsl:template match="vcsn:state">
    <xsl:value-of select="@name"/> [label="<xsl:value-of select="@label"/>",pos="<xsl:value-of select="child::vcsn:geometry/@x"/>,<xsl:value-of select="child::vcsn:geometry/@y"/>"];
  </xsl:template>

  <xsl:template match="vcsn:edge">
    <xsl:value-of select="@src"/>
	-> <xsl:value-of select="@dst"/>
	   [label="<xsl:value-of select="@label"/>"];
  </xsl:template>
</xsl:transform>
