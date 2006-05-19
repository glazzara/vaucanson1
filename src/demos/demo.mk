include $(top_srcdir)/src/vaucanson.mk

AM_CXXFLAGS += -DINTERNAL_CHECKS -DSTRICT

EXTRA_PROGRAMS = $(GENERATORS) $(TESTERS)

if VCSN_USE_XML
demos: $(TESTERS)
else
demos:
endif
