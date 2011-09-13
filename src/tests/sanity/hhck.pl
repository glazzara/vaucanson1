#!/usr/bin/perl -w
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2008, 2011 The Vaucanson Group.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The Vaucanson Group consists of people listed in the `AUTHORS' file.

# This file implements consistency checks between *.hh and *.hxx files.

use strict;

my $verb = 0;
sub verb(@)
{
  print @_, "\n" if $verb;
}

my $exit_code = 0;
sub err(@)
{
  print STDERR @_, "\n";
  $exit_code = 1;
}

# For debugging hashes of hashes
sub dumpf(%)
{
  require 'dumpvar.pl';
  dumpValue(\@_);
}


my $file;			# The actual name of the file.
my $inc_file;			# The stripped name of the file.

my $indent;	     # number of spaces expected at the start of line.
my $indentstr;			# " " x $indent
my $endnamespacestr;		# regex matching closing namespace.

sub init_file_variables($)
{
  ($file) = @_;

  # Strip the name of the file up to vaucanson/.  This way $inc_file
  # corresponds to the name of the file as it should appear after
  # #include <vaucanson/...> .
  ($inc_file = $file) =~ s:.*\bvaucanson/::;

  $indent = 0;
  $indentstr = "";
  $endnamespacestr = "}";
}

# matches start and end of namespaces
sub handle_namespace()
{
  if (m:^(\s*)namespace:)
    {
      err "$file:$.: misindented namespace"
	unless $1 eq $indentstr;
      $endnamespacestr = "$indentstr}\\s*(//.*)?";
      $indent += 2;
      $indentstr = " " x $indent;
      verb "$file:$.: begin namespace (ident = $indent)";
      return 1;
    }

  if (m:^$endnamespacestr:)
    {
      $indent -= 2;
      $indentstr = " " x $indent;
      $endnamespacestr = (" " x ($indent -  2)) . "}\\s*(//.*)?";
      verb "$file:$.: end namespace (ident = $indent)";
      return 1;
    }

  return 0;
}

# check include guards
sub handle_guard()
{
  if (m:^#ifndef\s+(\w+)\s+$:)
    {
      my $guard = $1;
      (my $expected = "VCSN_". $inc_file) =~ y:a-z./-:A-Z___:;
      verb "ifndef $1";
      err "$file:$.: guard should be \"$expected\""
	if $guard ne $expected;
      return 1;
    }
  return 0;
}

# read_hh and read_hxx both complete a hash table describing the file.
#
# At the first
# level, the keys are function names: each of them map to an
# array of hashes.  The array is needed to support overloaded
# definitions.  The subhashes may contains these entries:
#    pre       maps to a hash of preconditions defined in the hh file
#    precond   maps to a hash of preconditions defined in the hxx file
#    declloc   maps to the location of the function's declaration (hh)
#    specloc   maps to the location of the function's definition (hxx)
#
# E.g.
# { 'func1' => [
#                # first overload
#                { 'declloc' => 'file.hh:15',
#                  'pre' => { 'deterministic' => 1, 'complete' => 1 },
#                  'specloc' => 'file.hxx:60',
#                  'precond' => { 'deterministic' => 1 }
#                }
#                # second overload
#                { 'declloc' => 'file.hh:20',
#                  'specloc' => 'file.hxx:95',
#                }
#              ]
#   'func2' => [
#                etc.
#              ]
# }

sub read_hh($)
{
  my ($f) = @_;

  # Maps a function name to a structure describing the current function.
  my %functions = ();

  # Informations about the current function. Its name is not yet known
  # because we parse the comments before the prototype.
  my %current_function = ();

  init_file_variables $f;

  open FILE, "<$file" or die "Cannot open $file for reading";

  my $documented_file = 0;

  while (<FILE>)
  {
    # expand tabs
    s/\t/        /g;

    next if handle_guard;

    next if handle_namespace;

    if (m:\s+\/\*\*:)  # start of doxygen comment
      {
	err "$file:$.: failed to parse the name of the previous function"
	  unless 0 == keys(%current_function);
	next;
      }

    if (m:\*\s+\@file\s+([\w/.]+)\s*$:)  # @file comment
      {
	verb "file name: $1";
	err "$file:$.: \"\@file $1\" should be \"\@file $inc_file\""
	  if $inc_file !~ /\Q$1\E$/;
	$documented_file = 1;
	next;
      }

    if (m:\*\s+\@pre\s+(.*)$:)   # precondition
      {
	my $pre = $1;
	my @tags;
	push @tags, "realtime" if $pre =~ /\brealtime\b/;
#	push @tags, "boolean" if $pre =~ /\bboolean\b/;
	push @tags, "normalized" if $pre =~ /\bnormalized\b/;
	push @tags, "subnormalized" if $pre =~ /\bsub_normalized\b/;
	push @tags, "trim" if $pre =~ /\b(is_)?trim\b/;
	push @tags, "complete" if $pre =~ /\bcomplete\b/;
	push @tags, "deterministic" if $pre =~ /(?<!co-)\bdeterministic\b/;

	$current_function{"pre"}={} unless exists $current_function{"pre"};
	map {$current_function{"pre"}->{$_} = 1} @tags;

	verb "preconditions: @{[keys %{$current_function{'pre'}}]}";

	next;
      }

    if (m:^\s+};\s*$:) # end of struct or class
      {
	# ignore preconditions for structs or classes.
	%current_function = ();
      }

    if (m{^$indentstr(\w+)\s*\(.*(?:\)\;|,)\s*$}) # the name of a function.
      {
	$current_function{'declloc'} = "$file:$.";

	$functions{$1} = [] unless exists $functions{$1};
	push @{$functions{$1}}, {%current_function};
	%current_function = ();
	verb "function decl: $1 [$#{$functions{$1}}]";
      }
  };

  close FILE;

  err "$file: \@file documentation" unless $documented_file;

  return %functions;
}

sub read_hxx($@)
{
  my ($f, %functions) = @_;

  init_file_variables $f;

  open FILE, "<$file" or die "Cannot open $file for reading";

  my $current_function = "";
  my $current_function_n = 0;
  my $current_data;

  while (<FILE>)
  {
    # expand tabs
    s/\t/        /g;

    next if handle_guard;

    next if handle_namespace;

    if (m:^$indentstr(\w+)\s*\(:) # The name of a function.
      {
	if ($current_function eq $1)
	  {
	    ++$current_function_n;
	  }
	else
	  {
	    $current_function_n = 0;
	  }

	$current_function = $1;
	$functions{$1} = [] unless exists $functions{$1};

	$functions{$1}->[$current_function_n] = {}
  	  unless exists $functions{$1}->[$current_function_n];

	$current_data = $functions{$1}->[$current_function_n];

	$current_data->{'specloc'} = "$file:$.";

	verb "function def: $1 [$current_function_n]";

	next;
      }

    if (m:^$indentstr.+precondition\s*\((.*)\):) # preconditions
      {
	my $str = $1;
	$current_data->{"precond"} = {}
	  unless exists $current_data->{"precond"};

	my @p = ();
	push @p, "realtime" if $str =~ /is_realtime\(/;
	push @p, "trim" if $str =~ /is_trim\(/;
	push @p, "deterministic" if $str =~ /is_deterministic\(/;
	push @p, "normalized" if $str =~ /is_normalized\(/;
	push @p, "complete" if $str =~ /is_complete\(/;

	verb "preconditions: @p";

	map { $current_data->{"precond"}->{$_} = 1 } @p;
	next;
      }

    # Match calls of known functions so we can propagate preconditions
    foreach my $name (keys %functions)
      {
	if (m:\b$name\b\s*\(:)
	  {
	    # Iterate over all overloads of $fun.
	    # FIXME: We don't know which one to choose, so currently
	    # we do as if they were all called, which makes no sense.
	    foreach my $funinst (@{$functions{$name}})
	      {
		my $usage = $funinst->{"precond"};
		map { $current_data->{"precond"}->{$_} = 2 } (keys %$usage);
	      }
	  }
      }

  }

  return %functions;
}

# Match preconditions between hh and hxx files.
sub check_preconditions(@)
{
  verb "Checking preconditions";

  my %functions = @_;

  # dumpf %functions;

  foreach my $fun (keys %functions)
    {
      verb "checking $fun...";
      my $n = 0;
      # Iterate over all overloads of $fun.
      foreach my $funinst (@{$functions{$fun}})
	{
	  my $decl = $funinst->{"pre"};
	  my $usage = $funinst->{"precond"};

	  if (exists $funinst->{'declloc'}
	      and not exists $funinst->{'specloc'})
	    {
	      my $name = $fun;
	      $name = "@{[$n+1]}th overload of $name" if $n > 0;
	      err ("@{[$funinst->{'declloc'}]}: could not find matching "
		   . "definition of $name");
	    }

	  foreach my $key (keys %$decl)
	    {
	      my $name = $fun;
	      $name = "@{[$n+1]}th overload of $name" if $n > 0;
	      err ("@{[$funinst->{'declloc'}]}: $name() documents "
		   . "precondition '$key' but does not check it")
		unless exists $usage->{$key};
	    }
	  foreach my $key (keys %$usage)
	    {
	      my $name = $fun;
	      $name = "@{[$n+1]}th overload of $name" if $n > 0;

	      unless (exists $decl->{$key})
		{
		  # Only warn about underdocumented PUBLIC functions,
		  # i.e., functions that are declared in the *.hh file.
		  if (exists $funinst->{'declloc'})
		    {
		      err ("@{[$funinst->{'specloc'}]}: $name() checks "
			   . "precondition '$key' but does not document it");
		    }
		  else
		    {
		      verb ("@{[$funinst->{'specloc'}]}: skipping $name(), "
			    . "it does not seem to be public");
		    }
		}
	    }

	  ++$n;
	}
    }

  close FILE;
}

sub usage()
{
  print "$0 [OPTIONS]... [FILES]...

Check header files.  Make sure preconditions used in *.hxx files match
those documented in *.hh files.

Options:
  -h, --help		display this help and exit
  -v, --verbose         output debugging messages
";
  exit 0;
}

# Parse command line.
sub parse_arguments ()
{
  my %options =
    (
     'v|verbose' 	=> \$verb,
     'h|help'           => \&usage,
     );
  use Getopt::Long;
  Getopt::Long::config ("bundling", "pass_through");
  Getopt::Long::GetOptions %options or exit 1;
}


my %file_done;
parse_arguments();
foreach my $file (@ARGV)
{
  $file =~ s/\.hxx$/.hh/;

  next if exists $file_done{$file};
  $file_done{$file} = 1;

  my %infos = read_hh($file);
  (my $file_hxx = $file) =~ s/\.hh$/.hxx/;
  %infos = read_hxx($file_hxx, %infos);
  check_preconditions(%infos);
}

exit $exit_code;


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
