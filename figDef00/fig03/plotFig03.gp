set term svg size 350,350 fsize 13 
set size ratio 0.25 
set output "fig03.svg"
unset key
unset xlabel
unset ylabel
unset xtics

set xrange [382:454]

plot "./test00.txt" u 1:2 w l lc rgb "red",\
	"./test00.txt" u 1:5 w l lc rgb "green",\
	"./test00.txt" u 1:8 w l lc rgb "blue"
