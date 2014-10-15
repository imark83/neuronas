set term svg size 450,450 fsize 13 
set size ratio 0.15 
set output "fig07.svg"
unset key
unset xlabel
unset ylabel
unset xtics

#set xrange [382:454]

set multiplot

set origin 0,0.35
plot "./test00.txt" u 1:2 w l lc rgb "red",\
	"./test00.txt" u 1:5 w l lc rgb "green",\
	"./test00.txt" u 1:8 w l lc rgb "blue"


set origin 0.0,0.1
plot "./test00.txt" u 1:5 w l lc rgb "green"


set origin 0.0,-0.1
plot "./test00.txt" u 1:8 w l lc rgb "blue"


set origin 0.0,-0.35
plot "./test00.txt" u 1:2 w l lc rgb "red"

unset multiplot
