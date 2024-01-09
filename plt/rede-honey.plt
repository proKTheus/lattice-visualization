ARG1 = ARGV[1]
ARG2 = ARGV[2]

set palette defined (0 "#333333", 1 "#9dd926", 2 "#26acd9")

set terminal pngcairo
set output 'vis-honey'.ARG1.'-act-'.ARG2.'.png'

unset colorbox
set size square

set style data points
set style fill solid
set pointsize 4

unset xtics
unset ytics
#set xrange  [0:10]

plot '../dat/honey-rede'.ARG1.'-act'.ARG2.'.dat' using 1:2:4:(sprintf("%d",$4)) with labels center offset char 1,1 notitle, \
     '' using 1:2:3 with points pt 7 lc palette notitle




