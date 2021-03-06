set term svg size 800, 600
set output 'basin01_zoom.svg'

set xtics nomirror (0, "1/27" 0.33, "2/27" 0.66, "3/27" 0.9999)
set ytics (0, "1/27" 0.33, "2/27" 0.66, "3/27" 0.9999)
set cbtics ("no convergence" -1, "point 0 (0.54,0)" 0 , "point 1 (0,0.54)" 1, "point 2 (0.45,0.45)" 2, "point 3 (0.33,0.66)" 3, "point 4 (0.66,0.33)" 4)
unset key
set size square
set pm3d map
set cbrange [-1.5:4.5]
set xrange [0:1]
set yrange [0:1]
set xlabel "pulse 1 (-0.02 mA) start"
set ylabel "pulse 2 (+0.01 mA) start"
set title "control 01: 2 shocks (-,+) (0.05 P), different start"
set palette maxcolors 6
splot '< echo 0' matrix




