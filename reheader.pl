#! /usr/bin/perl -w
use strict;

my $boundupper = "#ifndef %CPPNAME%
# define %CPPNAME%";
my $boundlower = "#endif // %CPPNAME%";

my $header = "// %BASENAME%: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch\@enst.fr>
//    * Sylvain Lombardy <lombardy\@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole\@lrde.epita.fr>
//    * Loic Fosse <loic.fosse\@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen\@enst.fr>
//    * Raphael Poss <raphael.poss\@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas\@lrde.epita.fr>
//    * Maxime Rey <maxime.rey\@lrde.epita.fr>
//
";

my $fname = $ARGV[0];

$_ = $fname;
s,^./,,g;
s,^src/,,g;
s,^include/vaucanson/,,g;
my $shortname = $_;
s,.*/,,g;
my $basename = $_;

$_ = $shortname;
s,^[./]*,,g;
s,^,VCSN_,g;
s,[^a-zA-Z],_,g;
y/[a-z]./[A-Z]_/;
my $cppname = $_;

$_ = $boundupper;
s,%BASENAME%,$basename,g;
s,%CPPNAME%,$cppname,g;
my $xboundupper = $_;

$_ = $boundlower;
s,%BASENAME%,$basename,g;
s,%CPPNAME%,$cppname,g;
my $xboundlower = $_;

$_ = $header;
s,%BASENAME%,$basename,g;
s,%CPPNAME%,$cppname,g;
my $xheader = $_;


print STDERR "Processing for $fname...\n";

open(FILE, "<", $fname) or die "cannot open $fname: $!\n";

my $content;
while (<FILE>)
{
   $content .= $_;
}
close FILE;

$_ = $content;
s,^((/\*.*?\*/)|(//[^\n]*\n)|[ \t\n])*,,sg;
s,([ \t\n])*$,\n,sg;

if (/^# *ifndef[^\n]*\n[\n\t ]*# *define[^\n]*\n/s)
{
  s,^# *ifndef[^\n]*\n[\n\t ]*# *define[^\n]*\n,$xboundupper\n,sg;
}

if (/# *endif[^\n]*\n[\n\t ]*$/s)
{
  s,# *endif[^\n]*\n[\n\t ]*$,$xboundlower\n,sg;
}

s/^/$xheader/sg;

$content = $_;

my @mv = ("mv", "-f", "$fname", "$fname.bak");
system(@mv) == 0 or die "system @mv failed: $?\n";

open(FILE, ">", $fname) or die "cannot open $fname for writing: $!\n";
print FILE $content;

exit 0;

