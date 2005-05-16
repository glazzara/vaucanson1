AM_CXXFLAGS = $(CXXFLAGS_STRICT)
AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/include

TESTS_ENVIRONMENT= SRCDIR=$(srcdir)

b_tester_SOURCES = xml_automaton_tester.cc
b_tester_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_tester_SOURCES = xml_automaton_tester.cc
z_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

r_tester_SOURCES = xml_automaton_tester.cc
r_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/r_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::r_automaton"

z_max_plus_tester_SOURCES = xml_automaton_tester.cc
z_max_plus_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_max_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_max_plus_automaton"

z_min_plus_tester_SOURCES = xml_automaton_tester.cc
z_min_plus_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_min_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_min_plus_automaton"

fmp_tester_SOURCES = xml_fmp_tester.cc

trans_tester_SOURCES = xml_trans_tester.cc

session_tester_SOURCES = xml_session_tester.cc

if XML_CHECK
check_SCRIPTS = 				\
	tester.sh

TESTS = $(check_SCRIPTS)

check_PROGRAMS = 				\
	b_tester				\
	r_tester				\
	z_tester				\
	z_max_plus_tester			\
	z_min_plus_tester			\
	fmp_tester				\
	trans_tester				\
	session_tester				

CLEANFILES = vaucanson.xsd

$(check_SCRIPTS): vaucanson.xsd

vaucanson.xsd:
	ln -sf $(top_builddir)/doc/xml/vaucanson.xsd .

endif


EXTRA_DIST =					\
	xml_automaton_tester.cc			\
	xml_fmp_tester.cc			\
	xml_trans_tester.cc			\
	xml_session_tester.cc			\
	tester.sh				\
	b_ref.xml				\
	z_ref.xml				\
	r_ref.xml				\
	z_max_plus_ref.xml			\
	z_min_plus_ref.xml			\
	fmp_ref.xml				\
	trans_ref.xml				\
        b_ref.dot				\
        fmp_ref.dot				\
        r_ref.dot				\
        trans_ref.dot				\
        z_max_plus_ref.dot			\
        z_min_plus_ref.dot			\
        z_ref.dot				\
        b_ref.xml				\
        fmp_ref.xml				\
        r_ref.xml				\
        trans_ref.xml				\
        z_max_plus_ref.xml			\
        z_min_plus_ref.xml			\
        z_ref.xml
