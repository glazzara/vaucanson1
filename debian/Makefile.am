distdir = $(PACKAGE)-$(VERSION)
DIST_ARCHIVE = $(distdir).tar.gz

EXTRA_DIST =                                    \
        changelog                               \
        compat                                  \
        control                                 \
        copyright                               \
        files                                   \
	rules					\
        vaucanson-doc.docs                      \
	vaucanson-doc.examples			\
	vaucanson.docs				\
	vaucanson.install

deb: $(top_builddir)/$(DIST_ARCHIVE)
	rm -rf $(distdir)
	tar xvzf $<
	cd $(distdir) && dpkg-buildpackage -rfakeroot -us -uc
