#!/usr/bin/perl
# by Michael Soltys, December 2007

# This is a perl script for generating the first n bits of the 
# Mycielski-Ehrenfeucht sequence
# It can be invoked as  
#
#	string.pl n
#
# where n must be at least 4  (the program does not check that it is)
#
# The output consists of 3 columns:
#	-first column is the bit number of the sequence 
#		(the first 3 bits are 010 - they are given)
#	-second column is the number of 1s encountered by this position
#	-third column contains the % of 1s - the limit of this as n
#		grows is 0.5
#
# Finally, if program is invoked as
#
#	string.pl n strings
#
# then a 4th column is added containing the entire string so far; this
# could be useful if the actual string is wanted.

use List::Util qw[min max];

$n=$ARGV[0];
$m=1;
$s="010";

for ($i=2; $i<$n-1; $i++) {
	$found=0;
	$j=0;
	$l=length($s);
	while ($found==0) {
	   $j=$j+1;
	   $answer=-1;
	   for ($k=0; $k<$j; $k++) {
	      if (substr($s,$k,$l-$j) eq substr($s,$j,$l-$j)) {
		    $answer=$k;
	      }
	   }
	   if ($answer != -1) {
	      $found=1;
	   }
	}

	$new=substr($s,($answer+$l-$j),1);
	if ($new eq "1") {
		$s=$s."0";
	}
	else {
		$s=$s."1";
		$m=$m+1;
	}

	$nr=$i+2;
	$limit=$m/$nr;
	print "$nr:\t $m \t";
	printf "%.2f   ", $limit; 
	if ($ARGV[1] eq "strings") {
		print  "\t $s";
	}
	print "\n";

}
