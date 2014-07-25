clf
xx=linspace(-5.00000e-01,7.00000e-01,64);
yy=linspace(-5.00000e-01,5.00000e-01,64);
F = load ("FLI.txt");
[x,y] = meshgrid (xx,yy);
pcolor(x,y,F)
shading flat
axis([-5.00000e-01 7.00000e-01 -5.00000e-01 5.00000e-01])
