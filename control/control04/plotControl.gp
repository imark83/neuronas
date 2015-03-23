set term png size 800, 600
set output "basin00.png"

unset xtics
unset ytics
unset xlabel
unset ylabel
unset cbtics
unset cblabel
unset title
unset key



set size square
set pm3d map corners2color c1
set cbrange [-1.5:4.5]
set palette maxcolors 6
splot "./T.txt" matrix u ($1/512):($2/512):0



