#!/usr/bin/env perl

use strict;
use warnings;

sub usage()
{
    print "$0: Extract parameters and results from CBS XML files.\n";
    print "\n";
    print "Usage:\n";
    print "  $0 [options] [files...] \n";
    print "\n";
    print "Produce a gnuplot compatible output.  Values for one file\n";
    print "are printed on a single line and separated by whitespace.\n";
    print "Parameters come before results, and both are sorted in lexical\n";
    print "order.  See output for details.\n";
    print "\n";
    print "Note: Non-existant or incorrect (containing whitespace) values\n";
    print "      default to 0.\n";
    print "\n";
    print "Options:\n";
    print "\n";
    print "  -h: Display this help message.\n";
    print "\n";
    print "  -p <parameter>:\n";
    print "    Extract <parameter> from the parameters.\n";
    print "    Can be used multiple times.\n";
    print "\n";
    print "  -r <result>:\n";
    print "    Extract <result> from the result.\n";
    print "    Can be used multiple times.\n";
    print "\n";
    print "  -d <directory>:\n";
    print "    Include all .xml files in <directory>.\n";
    print "    Subdirectories are not included.\n";
    print "    Can be used multiple times.\n";
    print "\n";
    print "  -l <file>:\n";
    print "    Include all parameters and results present in <file>.\n";
    print "    The values in <file> are _not_ included in the output.\n";
    print "    Can be used multiple times.\n";
    print "\n";
    print "  -a:\n";
    print "    Extract all parameters and results from all files.\n";
    print "\n";
    print "Example:\n";
    print "\n";
    print "    $0 -p \"test depth\" -r time -d ../bench/xml -l ../dummy.xml\n";
    print "\n";
}

my %parameters;
my %results;
my @files;
my @dirs;
my @ref_files;
my $extract_all;

if (@ARGV == 0)
{
    usage();
    exit;
}

# Parse arguments
foreach (my $i = 0; $i < @ARGV; $i++)
{
    if ($ARGV[$i] eq "-h")
    {
	usage();
	exit;
    }
    if ($ARGV[$i] eq "-l")
    {
	$i += 1;
	$ref_files[$#ref_files + 1] = $ARGV[$i];
	next;
    }
    if ($ARGV[$i] eq "-a")
    {
	$extract_all = 1;
	next;
    }
    if ($ARGV[$i] eq "-p")
    {
	$i += 1;
	$parameters{$ARGV[$i]} = 0;
	next;
    }
    if ($ARGV[$i] eq "-r")
    {
	$i += 1;
	$results{$ARGV[$i]} = 0;
	next;
    }
    if ($ARGV[$i] eq "-d")
    {
	$i += 1;
	$dirs[$#dirs + 1] = $ARGV[$i];
	next;
    }
    $files[$#files + 1] = $ARGV[$i];
}

# Read directories
foreach (@dirs)
{
    if (opendir(DIR, $_))
    {
	my $dir = $_;
	while (my $file = readdir(DIR))
	{
	    if ($file =~ /\.xml$/)
	    {
		$files[$#files + 1] = "$dir/$file";
	    }
	}
	closedir DIR;
    }
    else
    {
	warn "Cannot open directory opendir $_: $!";
    }
}

# Handle -a
if ($extract_all)
{
    $ref_files[$#ref_files + 1] = $_ foreach (@files);
}

# Process reference files
foreach (@ref_files)
{
    if (open(my $in, "<", $_))
    {
	while (<$in>)
	{
	    last if (/<\/bench>/);
	    next unless (/<parameter / or /<result /);
	    if (/<parameter name="([^"]*)" value="([^"]*)" \/>/)
	    {
		$parameters{$1} = 0;
	    }
	    if (/<result name="([^"]*)" value="([^"]*)" \/>/)
	    {
		$results{$1} = 0;
	    }
	}
    }
    else
    {
	warn "Can't open reference file $_: $!";
    }
}

# Print header
my @parameters_keys = keys %parameters;
my @results_keys = keys %results;

@parameters_keys = sort @parameters_keys;
@results_keys = sort @results_keys;

print "# Benchmark results\n";
print "#\n";
print "# Parameters:\n";
print "#   * $_\n" foreach (@parameters_keys);
print "# Results:\n";
print "#   * $_\n" foreach (@results_keys);
print "# Files:\n";
print "#   * $_\n" foreach (@files);
print "#\n";

# Process files
foreach (@files)
{
    if (open(my $in, "<", $_))
    {
	$parameters{$_} = 0 foreach (@parameters_keys);
	$results{$_} = 0 foreach (@results_keys);
	while (<$in>)
	{
	    last if (/<\/bench>/);
	    next unless (/<parameter / or /<result /);
	    if (/<parameter name="([^"]*)" value="([^\s"]*)" \/>/)
	    {
		$parameters{$1} = $2 if defined $parameters{$1};
	    }
	    if (/<result name="([^"]*)" value="([^\s"]*)" \/>/)
	    {
		$results{$1} = $2 if defined $results{$1};
	    }
	}

	print $parameters{$parameters_keys[0]} if $parameters_keys[0];
	foreach (1 .. $#parameters_keys)
	{
	    print " $parameters{$parameters_keys[$_]}";
	}
	print " $results{$_}" foreach (@results_keys);
	print "\n";
    }
    else
    {
	warn "Can't open $_: $!";
    }
}
