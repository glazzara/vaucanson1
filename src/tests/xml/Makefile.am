AM_LDFLAGS = -lxerces-c -L@XERCESC@/lib
AM_CPPFLAGS = -I$(top_srcdir)/include \
              -I$(top_builddir)/include \
	      -I@XERCESC@/include
AM_CXXFLAGS = $(CXXFLAGS_STRICT)

TESTS_ENVIRONMENT= SRCDIR=$(srcdir)

CLEANFILES= vaucanson.dtd \
	    export_dynamic.test \
            export_session.test \
            export_static.test \
            import_dynamic.test \
            import_session.test \
            import_static.test \
            import_generic.test \
            nodata.test \
	    test.sh

if XML_CHECK
check_SCRIPTS= \
	export_dynamic.test \
	export_session.test \
	export_static.test \
	import_dynamic.test \
	import_session.test \
	import_static.test \
	import_generic.test \
        nodata.test
  TESTS=$(check_SCRIPTS)

$(check_SCRIPTS): vaucanson.dtd test.sh

test.sh: $(srcdir)/test.src
	cp $(srcdir)/test.src test.sh
	chmod +x test.sh

vaucanson.dtd:
	ln -sf $(top_builddir)/xml/vaucanson.dtd .
endif

EXTRA_DIST=test.src \
	export_dynamic-float.xml.ref \
	export_dynamic-numerical.xml.ref \
	export_dynamic-session.xml.ref \
	export_dynamic-simple.xml.ref \
	export_dynamic-transcoder.xml.ref \
	export_dynamic-tropical.xml.ref \
	export_session-float.xml.ref \
	export_session-numerical.xml.ref \
	export_session-session.xml.ref \
	export_session-simple.xml.ref \
	export_session-transcoder.xml.ref \
	export_session-tropical.xml.ref \
	export_static-float.xml.ref \
	export_static-numerical.xml.ref \
	export_static-session.xml.ref \
	export_static-simple.xml.ref \
	export_static-transcoder.xml.ref \
	export_static-tropical.xml.ref \
	import_dynamic-float.xml.ref \
	import_dynamic-numerical.xml.ref \
	import_dynamic-session.xml.ref \
	import_dynamic-simple.xml.ref \
	import_dynamic-transcoder.xml.ref \
	import_dynamic-tropical.xml.ref \
	import_generic-float.xml.ref \
	import_generic-numerical.xml.ref \
	import_generic-session.xml.ref \
	import_generic-simple.xml.ref \
	import_generic-transcoder.xml.ref \
	import_generic-tropical.xml.ref \
	import_session-float.xml.ref \
	import_session-numerical.xml.ref \
	import_session-session.xml.ref \
	import_session-simple.xml.ref \
	import_session-transcoder.xml.ref \
	import_session-tropical.xml.ref \
	import_static-float.xml.ref \
	import_static-numerical.xml.ref \
	import_static-session.xml.ref \
	import_static-simple.xml.ref \
	import_static-transcoder.xml.ref \
	import_static-tropical.xml.ref \
	nodata-float.xml.ref \
	nodata-numerical.xml.ref \
	nodata-session.xml.ref \
	nodata-simple.xml.ref \
	nodata-transcoder.xml.ref \
	nodata-tropical.xml.ref \
	float.xml \
	numerical.xml \
	session.xml \
	simple.xml \
	transcoder.xml \
	tropical.xml

.cc.test:
	ln -sf test.sh $@

if XML_CHECK
  check_PROGRAMS= \
	export_dynamic \
	export_session \
	export_static \
	import_dynamic \
	import_session \
	import_static \
	import_generic \
	nodata
endif

export_dynamic_SOURCES=export_dynamic.cc
export_session_SOURCES=export_session.cc
export_static_SOURCES=export_static.cc
import_dynamic_SOURCES=import_dynamic.cc
import_session_SOURCES=import_session.cc
import_static_SOURCES=import_static.cc
import_generic_SOURCES=import_generic.cc
nodata_SOURCES=nodata.cc
