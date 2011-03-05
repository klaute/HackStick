#!/usr/bin/perl -w

use strict;

my $text       = shift || exit -1;
my $delaystart = shift || 0xff;
my $delay      = shift || 0x0f;

my %keys = (
	"a" => "04",
	"b" => "05",
	"c" => "06",
	"d" => "07",
	"e" => "08",
	"f" => "09",
	"g" => "0A",
	"h" => "0B",
	"i" => "0C",
	"j" => "0D",
	"k" => "0E",
	"l" => "0F",
	"m" => "10",
	"n" => "11",
	"o" => "12",
	"p" => "13",
	"q" => "14",
	"r" => "15",
	"s" => "16",
	"t" => "17",
	"u" => "18",
	"v" => "19",
	"w" => "1A",
	"x" => "1B",
	"y" => "1C",
	"z" => "1D",
	"1" => "1E",
	"2" => "1F",
	"3" => "20",
	"4" => "21",
	"5" => "22",
	"6" => "23",
	"7" => "24",
	"8" => "25",
	"9" => "26",
	"0" => "27",
	"Return" => "28",
	"ESCAPE" => "29",
	"Backspace" => "2A",
	"Tab" => "2B",
	"Spacebar" => "2C",
	"-" => "2D",
	"=" => "2E",
	"[" => "2F",
	"]" => "30",
	"\\" => "31",
	"#" => "32",
	";" => "33",
	"‘" => "34",
	"'" => "35",
	"," => "36",
	"." => "37",
	"/" => "38",
	"Caps Lock" => "39",
	"F1" => "3A",
	"F2" => "3B",
	"F3" => "3C",
	"F4" => "3D",
	"F5" => "3E",
	"F6" => "3F",
	"F7" => "40",
	"F8" => "41",
	"F9" => "42",
	"F10" => "43",
	"F11" => "44",
	"F12" => "45",
	"PrintScreen" => "46",
	"Scroll Lock" => "47",
	"Pause" => "48",
	"Insert" => "49",
	"Home" => "4A",
	"PageUp" => "4B",
	"Entf" => "4C",
	"End" => "4D",
	"PageDown" => "4E",
	"RightArrow" => "4F",
	"LeftArrow" => "50",
	"DownArrow" => "51",
	"UpArrow" => "52",
);

my @chars = split("", $text);

my $cnt = 0;
my $shift = 0;
my $codes = "";
foreach my $char ( @chars )
{
    $cnt++;
    if ($char eq " ")
    {
        $codes .= pressShift();
        $shift = 1;
        $char = "Spacebar";
    } elsif ( $char eq "\n" )
    {
        $codes .= pressShift();
        $shift = 1;
        $char = "Return";
    } elsif ( $char eq ";" )
    {
        $codes .= pressShift();
        $shift = 1;
        $char = ",";
    } elsif ( $char eq ":" )
    {
        $codes .= pressShift();
        $shift = 1;
        $char = ".";
    } elsif ( $char eq "!" )
    {
        $codes .= pressShift();
        $shift = 1;
        $char = "1";
    } else {
        if ( lc($char) ne $char )
        {
            $codes .= pressShift();
            $shift = 1;
        } else {
            if ($shift)
            {
                $codes .= releaseShift();
                $shift = 0;
            } else {
                $codes .= "0x01\n"  # ein byte ändern
                       .  "0x02\n"; # an index 2
            }
        }
        $char = lc($char);
    }
    print $char. " = ". getUSBKeyCode($char). "; ";
    print "\n" if ( $cnt != 0 && $cnt % 10 == 0 );
    $codes .= "0x". getUSBKeyCode($char). "\n";
}

if ($shift) # prüfen ob ie shift-taste abgeschlaten werden muss
{
    $cnt++;
    $codes .= "0x01\n"; # 2 Bytes ändern
    $codes .= "0x00\n"; # erstes byte an index 0
    $codes .= "0x00\n"; # shift nicht mehr gedrückt
    $shift = 0;
}

print "\n---------\n";
print "0x08\n"; # 8 Bytes für USB Daten
printf("0x%02X\n",$delaystart); #"0xFF\n"; # x ms Delay vor dem Start
printf("0x%02X\n",$delay); # y ms Delay zwischen den Übertragungen
printf("0x%02X\n",$cnt); # Anzahl der Blöcke
print $codes; # erzeugte Daten

exit 0;

sub pressShift
{
    return  "0x02\n"  # 2 Bytes ändern
           ."0x00\n"  # erstes byte an index 0
           ."0x02\n"  # shift gedrückt
           ."0x02\n"; # zweites byte an index 2
}

sub releaseShift
{
    return  "0x02\n"  # 2 Bytes ändern
           ."0x00\n"  # erstes byte an index 0
           ."0x00\n"  # shift nicht mehr gedrückt
           ."0x02\n"; # zweites byte an index 2
}

sub getUSBKeyCode
{
    my $char = shift || return -1;

    return $keys{$char};

}

