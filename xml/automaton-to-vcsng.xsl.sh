#!/bin/sh

if [ "x$1" == x ]; then
  SRCDIR=.
else
  SRCDIR="$1"
fi

cat <<EOF >automaton-to-vcsng.xsl
<?xml version="1.0" encoding="iso8859-1" ?>
<!DOCTYPE transform>
<xsl:transform version="1.0"
	       exclude-result-prefixes="vcsn"
               xmlns:vcsn="http://www.lrde.epita.fr/vaucanson"
               xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="text"
               encoding="iso8859-1"/>

EOF

awk -f ${SRCDIR}/style-to-xsl-vcsng.awk <${SRCDIR}/vaucanson-g.style >>automaton-to-vcsng.xsl

cat <<EOF >>automaton-to-vcsng.xsl
  <xsl:template match="vcsn:automaton">
\begin{VCPicture}{(<xsl:value-of select="child::vcsn:geometry/@left"/>,<xsl:value-of select="child::vcsn:geometry/@bottom"/>)(<xsl:value-of select="child::vcsn:geometry/@right"/>,<xsl:value-of select="child::vcsn:geometry/@top"/>)}
<xsl:apply-templates/>
\end{VCPicture}
</xsl:template>

  <xsl:template match="vcsn:type"/>

  <xsl:template match="vcsn:structure">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:apply-templates select="child::vcsn:states"/>
    <xsl:apply-templates select="child::vcsn:edges"/>
    <xsl:apply-templates select="child::vcsn:initials"/>
    <xsl:apply-templates select="child::vcsn:finals"/>
  }
  </xsl:template>

  <xsl:template match="vcsn:states">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:apply-templates select="child::vcsn:state"/>
  }
  </xsl:template>

  <xsl:template match="vcsn:edges">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:apply-templates select="child::vcsn:edge"/>
  }
  </xsl:template>

  <xsl:template match="vcsn:initials">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:apply-templates select="child::vcsn:initial"/>
  }
  </xsl:template>

  <xsl:template match="vcsn:finals">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:apply-templates select="child::vcsn:final"/>
  }
  </xsl:template>

  <xsl:template match="vcsn:geometry">
    <xsl:apply-templates select="@*"/>
  </xsl:template>

  <xsl:template match="vcsn:state">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:variable name="name" select="@name"/>
    <xsl:variable name="list" select="ancestor-or-self::*/child::vcsn:geometry/@doubleline"/>
    <xsl:variable name="list2" select="//vcsn:final[@state=\$name]/ancestor-or-self::*/child::vcsn:geometry/@doubleline"/>
    <xsl:variable name="isfinal" select="count(//vcsn:final[@state=\$name])!=0"/>
    <xsl:choose>
      <xsl:when test="\$isfinal and \$list[position()=last()] = 'true'">
        \FinalState[<xsl:value-of select="@label"/>]{(<xsl:value-of select="child::vcsn:geometry/@x"/>,<xsl:value-of select="child::vcsn:geometry/@y"/>)}{<xsl:value-of select="@name"/>}
      </xsl:when>
      <xsl:when test="\$isfinal and \$list2[position()=last()] = 'true'">
        \FinalState[<xsl:value-of select="@label"/>]{(<xsl:value-of select="child::vcsn:geometry/@x"/>,<xsl:value-of select="child::vcsn:geometry/@y"/>)}{<xsl:value-of select="@name"/>}
      </xsl:when>
      <xsl:otherwise>
        \State[<xsl:value-of select="@label"/>]{(<xsl:value-of select="child::vcsn:geometry/@x"/>,<xsl:value-of select="child::vcsn:geometry/@y"/>)}{<xsl:value-of select="@name"/>}
      </xsl:otherwise>
    </xsl:choose>
  }
</xsl:template>

  <xsl:template match="vcsn:edge">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:variable name="curvature"
                  select="child::vcsn:geometry/@curvature"/>
    <xsl:variable name="curvside"
                  select="child::vcsn:geometry/@curvside"/>
    %% <xsl:value-of select="curvature"/>
    %% <xsl:value-of select="curvside"/>
    <xsl:choose>
      <xsl:when test="@src = @dst">
        \LoopN{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="not(\$curvature)">
        \EdgeL{<xsl:value-of select="@src"/>}{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="\$curvature='edge' and \$curvside='left'">
        \EdgeL{<xsl:value-of select="@src"/>}{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="\$curvature='edge' and \$curvside='right'">
        \EdgeR{<xsl:value-of select="@src"/>}{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="\$curvature='arc' and \$curvside='left'">
        \ArcL{<xsl:value-of select="@src"/>}{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="\$curvature='arc' and \$curvside='right'">
        \ArcR{<xsl:value-of select="@src"/>}{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
      <xsl:when test="\$curvature='loop'">
        \LoopN{<xsl:value-of select="@dst"/>}{<xsl:value-of select="@label"/>}
      </xsl:when>
    </xsl:choose>
  }
  </xsl:template>

  <xsl:template match="vcsn:initial">
    <xsl:choose>
      <xsl:when test="not(child::vcsn:geometry/@direction)">
        \Initial[w]{<xsl:value-of select="@state"/>}
      </xsl:when>
      <xsl:otherwise>
    \Initial[<xsl:value-of select="child::vcsn:geometry/@direction"/>]{<xsl:value-of select="@state"/>}
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="vcsn:final">
  { <xsl:apply-templates select="child::vcsn:geometry"/>
    <xsl:variable name="name" select="@state"/>
    <xsl:variable name="list" select="id(@state)/ancestor-or-self::*/child::vcsn:geometry/@doubleline"/>
    <xsl:variable name="list2" select="ancestor-or-self::*/child::vcsn:geometry/@doubleline"/>
    <xsl:choose>
      <xsl:when test="\$list[position()=last()] = 'true'" />
      <xsl:when test="\$list2[position()=last()] = 'true'" />
      <xsl:otherwise>
	<xsl:choose>
	  <xsl:when test="not(child::vcsn:geometry/@direction)">
	    \Final[w]{<xsl:value-of select="@state"/>}
	  </xsl:when>
	  <xsl:otherwise>
            \Final[<xsl:value-of select="child::vcsn:geometry/@direction"/>]{<xsl:value-of select="@state"/>}
	  </xsl:otherwise>
	</xsl:choose>
      </xsl:otherwise>
    </xsl:choose>
  }
  </xsl:template>

</xsl:transform>
EOF
