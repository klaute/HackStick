
package SyslogReader;

use strict;
use Parse::Syslog;
use POSIX qw/strftime/;

sub new
{
	my $self = {};
	my %args = @_ || ('DEBUG', 0);

	bless $self;
	unless ($self->Init(\%args))
	{
		warn "Syslog konnte nicht geöffnet werden!" if ( $self->{'DEBUG'} );
		return -1;
	}

	return $self;
}

sub Init
{
	my $self = shift;
	my $ref = shift || return -1;
	my %parameter = %{$ref};

	$self->{'DEBUG'} = $parameter{'DEBUG'} || 0;

	$self->{'parser'} = Parse::Syslog->new( '/var/log/kern.log');

	$self->read();
	$self->setAllRead();

	return 1;
}

sub setAllRead
{
	my $self = shift;

	foreach my $ts ( keys(%{$self->{'logdata'}}) )
	{
	        my $tmp = $self->{'logdata'}->{$ts};
	        my %th = %{$$tmp};
		if ( ! $th{'read'} )
		{
			# Logeintrag als gelesen markieren und Inhalt löschen
			${$self->{'logdata'}->{$ts}}->{'text'} = '';
			${$self->{'logdata'}->{$ts}}->{'read'} = 1;
		}
	}
}

sub read
{
	my $self = shift;

	while ( my $sl = $self->{'parser'}->next )
	{
     		my $timestamp = $sl->{timestamp};
		if ( $timestamp > ($self->{'lasttimestamp'} || 0) && $sl->{program} eq "kernel" )
		{
			$self->{'logdata'}->{$timestamp} = \{'read' => 0,  'text' => $sl->{text}};
		}
	}

	return 0;
}

sub getNext
{
	my $self = shift;

	$self->read();

	foreach my $ts ( sort( keys(%{$self->{'logdata'}}) ) )
	{
	        my $tmp = $self->{'logdata'}->{$ts};
	        my %th = %{$$tmp};
		if ( ! $th{'read'} )
		{
			# Logeintrag als gelesen markieren und Text löschen
			${$self->{'logdata'}->{$ts}}->{'text'} = '';
			${$self->{'logdata'}->{$ts}}->{'read'} = 1;
			return \%th;
		}
	}
	# Keine weiteren Zeilen im Logfile
	return 0;
}

1;


