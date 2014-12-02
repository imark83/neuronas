set term svg size 1000, 400 fsize 14
set output "fig3D_Hopf00.svg"

set xrange [0.118:0.542]
set zrange [0.456:0.882]
set yrange [-0.01876:-0.01871]
set view 56,118

unset key

splot	"./_r0.txt" u 2:1:3 w l lc rgb "red", \
	"./_g0.txt" u 2:1:3 w l lc rgb "green", \
	"./_b0.txt" u 2:1:3 w l lc rgb "blue", \
	"./_k0.txt" u 2:1:3 w l lc rgb "black", \
\
	"./_r1.txt" u 2:1:3 w l lc rgb "red", \
	"./_g1.txt" u 2:1:3 w l lc rgb "green", \
	"./_b1.txt" u 2:1:3 w l lc rgb "blue", \
	"./_c1.txt" u 2:1:3 w l lc rgb "cyan", \
\
	"./_cycle10.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle11.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle12.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle13.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle14.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle15.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle16.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle17.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle18.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle19.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle20.txt" u 2:1:3 w l lc rgb "magenta"
