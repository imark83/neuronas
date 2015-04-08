set term svg size 800,400
set output "control3-4.svg"
set ylabel "V"
set xlabel "time"
set yrange [-0.06:0.05]
plot "./neuron.txt" every 10 u 1:2 w l lc rgb "blue" title "neuron 1", \
	"./neuron.txt" every 10 u 1:3 w l lc rgb "red" title "neuron 2", \
	"./neuron.txt" every 10 u 1:4 w l lc rgb "green" title "neuron 3"

