pkgdata_DATA = automaton-to-dot.xsl \
	       automaton-to-neato.xsl \
	       automaton-to-vcsng.xsl \
	       vaucanson.dtd

CLEANFILES = vaucanson.dtd automaton-to-vcsng.xsl

vaucanson.dtd: vaucanson-g.style style-to-dtd.awk gendtd.sh
	$(SHELL) $(srcdir)/gendtd.sh $(srcdir)

automaton-to-vcsng.xsl: automaton-to-vcsng.xsl.sh vaucanson-g.style style-to-xsl-vcsng.awk
	$(SHELL) $(srcdir)/automaton-to-vcsng.xsl.sh $(srcdir)

EXTRA_DIST = automaton-to-dot.xsl \
	     automaton-to-neato.xsl \
	     automaton-to-vcsng.xsl.sh \
	     gendtd.sh \
	     vaucanson-g.style \
	     style-to-code.awk \
	     style-to-dtd.awk \
	     style-to-geometryvalue.awk \
	     style-to-tex.awk \
	     style-to-xsl-vcsng.awk
