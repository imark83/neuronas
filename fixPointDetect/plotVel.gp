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
splot "./T.txt" matrix u ($1/512):($2/512):0



