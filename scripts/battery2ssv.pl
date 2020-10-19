#!/usr/bin/perl

use warnings;
use strict;

# output is in the format:
# recnum id subid value
#
# No time is available presently, so recnum is just a number that is
# incremented by counting the 102 messages, which seem to be the most
# frequent.  This allows the script to keep some semblance of time
# correlation amongst the data.
#
# ID is 0-23 for battery voltage (0x6f2)
#       24-28 for battery temp (0x6f2)
#           subid 1-4 corresponds to values d1-d4
#       102 for whole battery pack: (0x102)
#           subid 0 for voltage
#           subid 1 for current
#           subid 2 for unfiltered current
#           subid 3 for negative terminal temperature
#       302 for state of charge: (0x302)
#           subid 0 for minimum %
#           subid 1 for UI %

# making this useful for gnuplot:
# bin/tescandump  data/candata.battery.test.bin | scripts/battery2ssv.pl | sort -k 2,3 -k 1n | awk '{ if ((lid != $2) || (lsid != $3)) { lid = $2; lsid = $3; if (NR > 1) { printf("\n\n"); } printf("\"id/subid=%s %s\"\n",$2,$3); } print; }' >battery.test.dat
#
# In gnuplot:
# plot for [IDX=0:117] 'battery.test.dat' i IDX u 0:4 w dots notitle

# another approach:
# bin/tescandump  data/candata.battery.test.bin | scripts/battery2ssv.pl >battery.dat
# sort -k 2,3 -k 1n battery.dat | awk '{ if ($2<=23) { if ((lid != $2) || (lsid != $3)) { lid = $2; lsid = $3; if (NR > 1) { printf("\n\n"); } printf("\"id/subid=%s %s\"\n",$2,$3); } print; } }' >battery.volts.dat
# sort -k 2,3 -k 1n battery.dat | grep " 302 0 " >soc.dat
#
# in gnuplot:
# plot for [IDX=0:83] 'battery.volts.dat' i IDX u 1:4 w lines notitle
# set y2tics
# set ylabel "Volts"
# set y2label "soc%"
# set xlabel "minutes"
# plot for [IDX=0:83] 'battery.volts.dat' i IDX u ($1/60000):4 w lines axes x1y1 notitle, 'soc.dat' u ($1/60000):4 w lines axes x1y2 notitle

my $recnum = 0;
my $index6f2 = 0;
# just used for decoding index numbers
my $meh = 0;

while (<>)
{
    chomp;
    if (/^time /)
    {
	($meh, $recnum) = split(/\s+/);
    }
    elsif (/^Battery pack:/)
    {
	s/[AVC]//g; # hide units
	my @vals = split(/\s+/);
	print "$recnum 102 0 $vals[2]\n";
	print "$recnum 102 1 $vals[3]\n";
	print "$recnum 102 2 $vals[4]\n";
	print "$recnum 102 3 $vals[5]\n";
	$recnum++;
    }
    elsif (/^State of charge minimum:/)
    {
	s/%//g; # hide units
	my @vals = split(/\s+/);
	print "$recnum 302 0 $vals[4]\n";
    }	
    elsif (/^State of charge UI:/)
    {
	s/%//g; # hide units
	my @vals = split(/\s+/);
	print "$recnum 302 1 $vals[4]\n";
    }
    elsif (/^Index:/)
    {
	($meh, $index6f2) = split(/\s+/);
    }
    elsif (/^d[1234]:/)
    {
	s/[d:]//g; 
	my ($subid, $val, $unit) = split(/\s+/);
	print "$recnum $index6f2 $subid $val\n";
    }
}
