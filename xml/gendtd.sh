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
<!ELEMENT automaton (geometry?, type, content)>
<!ELEMENT type (monoid, semiring?)>
<!ELEMENT content (geometry?, states, transitions, initials, finals)>
<!ELEMENT monoid (generator*|monoid*)>
<!ELEMENT semiring (monoid?, semiring?)>
<!ELEMENT states (geometry?, state*)>
<!ELEMENT transitions (geometry?, transition*)>
<!ELEMENT state (geometry?)>
<!ELEMENT transition (geometry?)>
<!ELEMENT initials (geometry?, initial*)>
<!ELEMENT finals (geometry?, final*)>
<!ELEMENT generator EMPTY>
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
    Pure means here "without any spontaneous transition"
  -->
<!ATTLIST automaton
	xmlns	CDATA	#FIXED "http://www.lrde.epita.fr/vaucanson"

	name	ID	#IMPLIED
>

<!--
Monoid node.
  -->
<!ATTLIST monoid
	type	(unit|free|product|CPFM|FCM|FC)
			"free"
	generators
		(letters|pairs|weigthed|integers)
			"letters"
>

<!--
Semiring node.
If you want to write a tranducer, you have to specify that the semiring is
constructed from a free monoid.
  -->
<!ATTLIST semiring
	operations
	(boolean|numerical|tropicalMax|tropicalMin|function|hadamard|shuffle)
			"numerical"
	set	(B|Z|R|ratseries)
			"B"
>

<!ATTLIST generator
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

<!ATTLIST transition
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
