#!/usr/bin/perl -w

my @words = ();

while (<>) {
    $_ .= <> while s/\\$//;
    if (s/^\s*\#\s*(if|ifdef|ifndef|elif)\s+//) {
	s(/\*.*?\*/)();
	s(/\*.*)();
	foreach my $word (split (/\W+/))
	{
	    next if $word eq 'defined' || $word !~ /^[a-zA-Z_]/;
	    push @words, $word;
	}
    }
}

print "cat \${1+\"\$\@\"} | sed -e 's,PACKAGE,VCSN_PACKAGE,g;s, VERSION, VCSN_VERSION,g' | egrep '^#.*(VCSN_|" . join ('|', @words), ")'\n";
