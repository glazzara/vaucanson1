#! /usr/bin/perl -w
# Extract all examples from the manual source.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307  USA

# This file was derived from a shell-script by Franc,ois Pinard for
# GNU M4, and rewritten in Perl by Akim Demaille.  Since then derived
# versions are used in various places, such as Bison, Tiger Compiler
# Assignments, etc.  This is the first LaTeX version to the author's
# knowledge.

use strict;
use IO::File;
# Comes with libtext-shellwords-perl.deb.
use Text::Shellwords;
use Text::Wrap;
use File::Basename;
use Getopt::Long qw(GetOptions);
use Pod::Usage qw(pod2usage);

my $me = basename ($0);

# The result of option parsing.  Keys include `srcdir', and `output-dir'.
my %option;

# The output directory.
my $odir;

# Dependencies of KEY as a simple string.
my %dependency;
# Set to 1 if KEY is not to keep as a dependency.
my %ignore;


# &DEPEND ($TARGET, @DEPENDENCY)
# ------------------------------
sub depend ($@)
{
  my ($target, @dependency) = @_;
  @dependency = (grep { !exists $ignore{$_} } @dependency);
  # print STDERR "$target: @dependency\n";
  push @{$dependency{$target}}, @dependency
    if @dependency;
}

# List of files already opened.  $FILE{FILE} is where FILE was
# first defined.
my %file;


# &register ($FILE)
# -----------------
# Make sure the $FILE name is used only once (as input or output), to
# avoid clashes.
sub register ($)
{
  my ($file) = @_;
  die "$ARGV: $.: no file name given"
    unless $file;
  die "$ARGV: $.: $file already used in $file{$file}"
    if $file{$file};
  $file{$file} = "$ARGV:$.";
}


# example_to_verbatim(CODE)
# -------------------------
# Strip Texinfo markup.
sub example_to_verbatim ($)
{
  my ($contents) = @_;

  $contents =~ s/^\@(c |comment|dots|end (ignore|group)|ignore|group).*$//gm;
  # Remove the Texinfo tags.
  $contents =~ s/^\@(error|result)\{\}//gsm;
  $contents =~ s/\@([{@}])/$1/gsm;
  $contents =~ s/^\@comment.*//gm;

  return $contents;
}


# &MESSAGE (@MESSAGE)
# -------------------
# Report some @MESSAGE to the user.
sub message (@)
{
  print STDERR "$me: $ARGV:$.: ", @_, "\n";
}


# &STORE ($FILE, $CONTENTS)
# -------------------------
# Save the $CONTENTS in the $FILE, unless it already contains $WHAT.
sub store ($$)
{
  my ($file, $contents) = @_;

  if (!-d dirname $file)
    {
      system ("mkdir -p " . dirname $file);
    }

  if (-f $file)
    {
      local $/;			# Turn on slurp-mode.
      my $linenum = $.;
      my $f = new IO::File "< $file"
	or die "$me: cannot open $file for reading: $!\n";
      my $old_contents = $f->getline;
      if ($old_contents eq $contents) 
	{
	  $. = $linenum;
	  message "$file: unchanged";
	  return;
	}
    }
  my $out = new IO::File (">$file")
    or die "$me: cannot create $file: $!\n";
  print $out $contents;
  message "$file: new";
}


# Return the set of dependencies of a shell pipe.
# This is a very crude approximation.
sub pipe_args ($)
{
  my ($pipe) = @_;
  chomp $pipe;

  # shellwords does not split `>foo' into `>' and `foo'.
  $pipe =~ s/([<|>])(\w)/$1 $2/g;

  my @words = shellwords ($pipe);
  my @res = ();

  my $state_initial = 0;
  my $state_verb = 1;
  my $state_arguments = 2;
  my $state = $state_initial;

  while ($_ = $words[0])
    {
      if ($state == $state_initial)
	{
	  if ($_ =~ /vcsn-\w+/)
	    {
	      $state = $state_verb;
	    }
	  else
	    {
	      $state = $state_arguments;
	    }
	}
      elsif ($state == $state_verb)
	{
	  # Shift the verb.
	  my $verb = shift @words;
	  # After a verb come arguments.
	  $state = $state_arguments;

	  if ($verb eq 'dump-automaton')
	    {
	      # We are looking for a standard automaton, no need
	      # to create it.
	      shift @words;
	    }
	  elsif ($verb =~ m/eval|power/)
	    {
	      # VERB AUTOMATON LITERAL.
	      # So strip the LITERAL, leave the AUTOMATON.
	      my $aut = shift @words;
	      shift @words;
	      unshift @words, $aut;
	    }
	  elsif ($verb eq 'standard')
	    {
	      # Ignore ratexps.
	      shift @words;
	      message "IGNORING: @words\n";
	    }
	  elsif ($verb =~ /^--/)
	    {
	      # Ignore options.
	      shift @words;
	      # But still expecting a verb.
	      $state = $state_verb;
	    }
	  # Skip the command only (at the end of the loop, there is a shift).
	  unshift @words, "XXX";
	}
      elsif ($state == $state_arguments)
	{
	  if ($_ eq "|")
	    {
	      $state = $state_initial;
	    }
	  elsif ($_ eq "-")
	    {
	      # Ignore.
	    }
	  elsif ($_ eq ">")
	    {
	      # What follows is not a dependency, this is a file we create.
	      # So skip it.
	      shift @words;
	    }
	  else
	    {
	      # These are arguments.
	      push @res, $_;
	    }
	}

      shift @words;
    }

  message "pipe_args ($pipe) = @res\n";
  return @res;
}


# Process one file.
sub process ($)
{
  # $ARGV is a global variable usually set by `<>' uses.
  $ARGV = "$option{srcdir}/$_[0]";
  my $file = new IO::File $ARGV;
  while ($_ = $file->getline)
    {
      ## \includegenerateddot{file}
      ## ==========================
      if (/\\includegenerateddot{(.*?)}/)
	{
	  my $file = $1;
	  register $file;
	  store "$odir/$file.file", "$file.dot";
	  depend "html", "$file.png";
	  depend "pdf", "$file.pdf";
	  depend "txt", "$file.txt";
	  depend "dvi", "$file.eps";
	}


      ## \execcaption{node}{command}
      ## ===========================
      ## Running `havm', `mipsy', `tc', or `sed' on the ARGS.
      elsif (/^\\execcaption{(.+?)}{(.+?)}/)
	{
	  my $node = $1;
	  my $command = "$2\n";
	  my $tex = "$node.tex";
	  register $tex;
	  store "$odir/$node.cmd", $command;
	  depend "tex", $tex;

	  # We might create output files here.
	  my @outs = grep { /^>(.*)/ } shellwords ($command);
	  foreach my $out (@outs)
	    {
	      $out =~ s/^>//;
	      depend $out, $tex;
	    }

	  # Dependencies: args except options and output redirections.
	  depend $tex, pipe_args ($command);
	}
    }
}


# The directory where to store the extracted results.
# Parse our options, trying to retain backwards compatibility with pod2man but
# allowing short forms as well.  --lax is currently ignored.
Getopt::Long::config ('bundling_override');
GetOptions (\%option,
	    'srcdir|s=s',
	    'top_srcdir=s',
	    'builddir=s',
	    'top_builddir=s',
	    'output-dir=s',
	    'help|h') or exit 1;
pod2usage (0) if $option{help};

$odir = $option{"output-dir"} || "extract";
if (! -d $odir)
{
  mkdir $odir or die "$me: cannot create $odir: $!\n";
}

my $makefile = new IO::File "> $odir/makefile"
  or die "$me: cannot create $odir/makefile: $!\n";

sub print_dir ($$)
{
  my ($var, $dir) = @_;
  use File::Spec;
  print $makefile $var, " = ", File::Spec->rel2abs ($dir), "\n";
}

print_dir ("extdir", "$odir");
print_dir ("srcdir", "$option{srcdir}");
print_dir ("builddir", "$option{builddir}");
print_dir ("top_srcdir", "$option{top_srcdir}");
print_dir ("top_builddir", "$option{top_builddir}");

print $makefile <<\EOF;
include $(srcdir)/extex.mk

.PHONY: all dvi eps html pdf tex txt

# all: txt

debug:
	echo "extdir = $(extdir) ($$(cd $(extdir) && pwd))"
	echo "srcdir = $(srcdir) ($$(cd $(srcdir) && pwd))"
	echo "builddir = $(builddir) ($$(cd $(builddir) && pwd))"
	echo "top_srcdir = $(top_srcdir) ($$(cd $(top_srcdir) && pwd))"
	echo "top_builddir = $(top_builddir) ($$(cd $(top_builddir) && pwd))"

EOF
my $example;
my $last_content;

depend "html", "tex";
depend "pdf",  "tex";
depend "txt",  "tex";
depend "dvi",  "tex";

process ($_)
  foreach @ARGV;

for my $target (sort keys %dependency)
{
  ## print $makefile ".PHONY: $target\n";
  # Using "map" only to get some functional composition of s///,
  # but there is a single string here.
  # print STDERR "wrap ($target ", @{$dependency{$target}}, ")\n";
  # FIXME: This wrapping may occur inside $target or any word of
  # $dependency if one of these is too long, thus cutting it in two!
  print $makefile (map ({ s/$(?!\z)/ \\/gm; $_ }
			wrap ("$target: ",
			      " " x length ("$target: "),
			      sort @{$dependency{$target}})),
		   "\n");
}

### Setup "GNU" style for perl-mode and cperl-mode.
## Local Variables:
## perl-indent-level: 2
## perl-continued-statement-offset: 2
## perl-continued-brace-offset: 0
## perl-brace-offset: 0
## perl-brace-imaginary-offset: 0
## perl-label-offset: -2
## cperl-indent-level: 2
## cperl-brace-offset: 0
## cperl-continued-brace-offset: 0
## cperl-label-offset: -2
## cperl-extra-newline-before-brace: t
## cperl-merge-trailing-else: nil
## cperl-continued-statement-offset: 2
## End:
