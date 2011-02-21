
package HackStick;

use strict;
use Device::SerialPort;

sub new
{
	my $self = {};
	my %args = @_;

	bless $self;
	unless ($self->Init(\%args))
	{
		warn "Device konnte nicht geöffnet werden!" if ( $self->{'DEBUG'} );
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

	$self->{'PortObj'} = new Device::SerialPort($parameter{'HackStick'}, 1) || die "Can't open ". $parameter{'HackStick'}. ": $!\n";

	$self->{'PortObj'}->baudrate(9600);
	#$self->{'PortObj'}->parity("odd");
	$self->{'PortObj'}->databits(8);
	$self->{'PortObj'}->stopbits(1);
	$self->{'PortObj'}->buffers(4096, 4096);
	$self->{'PortObj'}->parity_enable(0);

	return 1;
}

sub send
{
	my $self = shift;
	my $output_string = shift || return -1;
	$output_string .= "\r";

	warn "send: $output_string\n" if ( $self->{'DEBUG'} );

	my $count_out = $self->{'PortObj'}->write($output_string);
	unless ($count_out)
	{
		warn "write failed\n" if ( $self->{'DEBUG'} );
		return -2;
	}
	if ( $count_out != length($output_string) )
	{
		warn "write incomplete\n" if ( $self->{'DEBUG'} );
		return -3;
	}

	return 1;
}

sub read
{
	my $self = shift;
	my $STALL_DEFAULT=10; # how many seconds to wait for new input

	my $timeout=$STALL_DEFAULT;

	$self->{'PortObj'}->read_char_time(0);     # don't wait for each character
	$self->{'PortObj'}->read_const_time(1000); # 1 second per unfulfilled "read" call

	my $chars=0;
	my $buffer="";
	my $count = 1;
	while ($count>0 && $timeout > 0)
	{
		my $saw = "";
		($count,$saw)=$self->{'PortObj'}->read(1); # will read _up to_ 255 chars
		if ($count > 0)
		{
			$chars+=$count;
			$buffer.=$saw;

			# Check here to see if what we want is in the $buffer
			# say "last" if we find it
		} else {
			$timeout--;
		}
	}

	if ( $timeout == 0 )
	{
		warn "Timeout while reading...\n" if ( $self->{'DEBUG'} );
	}

	warn "\nread: [$buffer]\n\n" if ( $self->{'DEBUG'} );

	return $buffer;
}

1;

