# Provide the targets "dist", "distdir", and "distcheck".
# The latter only runs "make".
#
# Expects the contents to be shipped to be declared in data_DATA,
# or EXTRA_DIST.

data_DATA += $(EXTRA_DIST)

data_DATA +=	\
share		\
Makefile

DISTDIR = $(BASE)
TARBALL = $(DISTDIR).tar.gz
dist: distdir
	tar zcf $(TARBALL) $(DISTDIR)
	rm -rf $(DISTDIR)

# File to remove from the tarball.
DIST_IGNORE = \
  -name '*~' -o -name '.svn' -o -name '+committed'
distdir:
	rm -rf $(DISTDIR)
	mkdir $(DISTDIR)
# Use tar, not cp, to preserve the directory parts (cp bar/baz foo/ yields
# foo/baz, not foo/bar/baz).
	tar cf - $(data_DATA) | (cd $(DISTDIR) && tar xf -)
	find $(DISTDIR) $(DIST_IGNORE) | xargs rm -fr

distcheck: dist
	rm -rf _tests
	mkdir _tests
	cd _tests && tar zxf ../$(TARBALL)
	make -C _tests/$(DISTDIR)
	rm -rf _tests

.PHONY: distdir dist distcheck
