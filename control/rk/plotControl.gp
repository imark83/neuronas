#set term png size 800, 600
#set output "basin01.png"

set xtics nomirror (0, "1/3" 0.33, "2/3" 0.66, "1" 0.99)
set ytics (0, "1/3" 0.33, "2/3" 0.66, "1" 0.99)
set cbtics ("no convergence" -1, "point 0 (0.54,0)" 0 , "point 1 (0,0.54)" 1, "point 2 (0.45,0.45)" 2, "point 3 (0.33,0.66)" 3, "point 4 (0.66,0.33)" 4)
unset key
set size square
set pm3d map
#set xrange [0:(511./512)]
#set yrange [0:(511./512)]
set cbrange [-1.5:4.5]
set xlabel "shock 1 start"
set ylabel "shock 2 start"
set title "control 01: 2 shocks (-,+) (0.05 P), different start"
set palette maxcolors 6
splot "./T.txt" matrix u ($1/512):($2/512):0



