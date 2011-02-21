#!/usr/bin/perl

use strict;

use HackStick;
use SyslogReader;

use vars qw(@descriptor @data);

my $device = shift || "/dev/ttyUSB0";
my $script = shift || "script.pl";

my $ser = new HackStick($device, DEBUG=>1);
my $log = new SyslogReader(DEBUG=>1);

if ( $ser )
{

	# Abschalten des Echos
	$ser->send("ttye 0");
	$ser->read();

	while (checkLogfile() ne "")
	{
		# do nothing
	}

	my $stat = 0;

	while (1)
	{
		eval($script);
		sendNextChunk(DESCR => \@descriptor, DATA => \@data);
		checkLogfile();
		$stat++;
	}

}

exit 0;

sub sendNextChunk()
{
	my %args = @_;

	print "%args\n";

	$ser->send("sdsc");
	$ser->read();

		$ser->send("0x01");
		$ser->read();

	$ser->send("sdta");
	$ser->read();

		$ser->send("0x01");
		$ser->read();

	$ser->send("E");
	$ser->read();
	$ser->send("gdta");
	return $ser->read();
}

sub checkLogfile()
{
	my $entry = $log->getNext();
	if ( $entry )
	{
		if ( $$entry{'text'} =~ /segmentation fault/igm )
		{
			print "FOUND SEGFAULT!!!\n";
			return 1;
		} else {
			return 0;
		}
	} else {
		return "";
	}
}

