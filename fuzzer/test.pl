#!/usr/bin/perl -w

use strict;
use Data::Dumper;

use vars qw(@descriptor @data);

my $script = "script.pl";

my $stat = 2;

eval($script);

print Dumper(@data);

print @descriptor;
print @data;

