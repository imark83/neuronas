set xrange [0.118:0.542]
set zrange [0.456:0.882]
set yrange [-0.01886:-0.01871]

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
	"./_r2.txt" u 2:1:3 w l lc rgb "red", \
	"./_g2.txt" u 2:1:3 w l lc rgb "green", \
	"./_b2.txt" u 2:1:3 w l lc rgb "blue", \
\
	"./_cycle05.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle06.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle07.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle08.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle09.txt" u 2:1:3 w l lc rgb "magenta", \
	"./_cycle10.txt" u 2:1:3 w l lc rgb "magenta"
