cat ${1+"$@"} | sed -e 's,PACKAGE,VCSN_PACKAGE,g;s, VERSION, VCSN_VERSION,g' | egrep '^#.*(VCSN_|VCSN_CONFIG_SYSTEM_HH|HAVE_LIMITS|__GNUC__|__GNUC__)'
