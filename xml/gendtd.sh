#!/bin/sh

if [ "x$1" == x ]; then
  SRCDIR=.
else
  SRCDIR=$1
fi

cat >vaucanson.dtd <<EOF
<!--
  This DTD describes Vaucanson automaton. The aim of this representation is
  to be able to describe any automaton

  -->

<!-- Document structure -->
<!ELEMENT session (geometry?, automaton*)>
<!ELEMENT automaton (geometry?, type, structure)>
<!ELEMENT type (monoid, semiring?)>
<!ELEMENT structure (geometry?, states, edges, initials, finals)>
<!ELEMENT monoid (letter*)>
<!ELEMENT semiring (letter*)>
<!ELEMENT states (geometry?, state*)>
<!ELEMENT edges (geometry?, edge*)>
<!ELEMENT state (geometry?)>
<!ELEMENT edge (geometry?)>
<!ELEMENT initials (geometry?, initial*)>
<!ELEMENT finals (geometry?, final*)>
<!ELEMENT letter EMPTY>
<!ELEMENT initial (geometry?)>
<!ELEMENT final (geometry?)>
<!ELEMENT geometry EMPTY>

EOF

awk -f ${SRCDIR}/style-to-dtd.awk <${SRCDIR}/vaucanson-g.style >>vaucanson.dtd

cat >>vaucanson.dtd <<EOF

<!ATTLIST session
	xmlns	CDATA	#FIXED "http://www.lrde.epita.fr/vaucanson"
>
<!-- attributes of the root node -->
<!--
  xmlns:
    this attribute is used to embed automaton into another document
  type:
    Here are some properties of that can determinize the possible
    implementation.
  labels:
    Pure means here "without any spontaneous edge"
  -->
<!ATTLIST automaton
	xmlns	CDATA	#FIXED "http://www.lrde.epita.fr/vaucanson"

	type    (determinized|codeterminized|nonambiguous|invalued|any)
	                "any"
	labels	(series|polynoms|words|couples|letters|pure)
	                "letters"
	result	(product|determinization|standard|thompson|none)
	                "none"
>

<!--
Monoid node. At this moment, it can only be a classical free monoid.
  -->
<!ATTLIST monoid
	structural
		(letters|any)
			"letters"
	set	(words)
			"words"
>

<!--
Semiring node.
If you want to write a tranducer, you have to specify that the semiring is
constructed from a free monoid.
  -->
<!ATTLIST semiring
	structural
		(numerical|tropicalMax|tropicalMin|words)
			"numerical"
	set	(B|Z|R|words)
			"B"
>

<!--
ASCII
  -->
<!ATTLIST letter
	value	CDATA	#REQUIRED
>

<!--
        Weight is used only when labels are couples. (For series and polynoms,
        please use regular expression in labels instead).
  -->
<!ENTITY % serie-value
        'label   CDATA   "1"
	 weight  CDATA   #IMPLIED'
>

<!--
        Please number all or no state.
        In relative mode, positionment is made like in a table.
  -->
<!ATTLIST state
	name	ID	#REQUIRED
	number	CDATA	#IMPLIED
        label   CDATA   #IMPLIED
>

<!ATTLIST edge
	name	ID	#IMPLIED
	src	IDREF	#REQUIRED
	dst	IDREF	#REQUIRED

	%serie-value;
>

<!ATTLIST initial
        state   IDREF   #REQUIRED
	%serie-value;
>

<!ATTLIST final
        state   IDREF   #REQUIRED
	%serie-value;
>
EOF
