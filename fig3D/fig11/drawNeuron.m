clear
clc
clf

T = load ("T.txt");
hold on;

n = size(T)(1);
m = size(T)(2);

for i=1:n
	phi2 = mod((T(i,(m/3+1):(2*m/3-1))-T(i,1:(m/3-1)))./(T(i,2:(m/3))-T(i,1:(m/3-1))),1);
	phi3 = mod((T(i,(2*m/3+1):(m-1))-T(i,1:(m/3-1)))./(T(i,2:(m/3))-T(i,1:(m/3-1))),1);

	for j=2:m/3-2
		if (phi2(j) - phi2(j-1) > 0.5)
			phi2(j) = phi2(j)-1;
		end
		if (phi2(j-1) - phi2(j) > 0.5)
			phi2(j) = phi2(j)+1;
		end
		if (phi3(j) - phi3(j-1) > 0.5)
			phi3(j) = phi3(j)-1;
		end
		if (phi3(j-1) - phi3(j) > 0.5)
			phi3(j) = phi3(j)+1;
		end
	end
	
	point0(i,:) = [phi2(1), phi3(1)];
	point(i,:) = [phi2(end), phi3(end)];
	plot (phi2(1), phi3(1), 'or');
	plot (phi2, phi3, '-b');
	%axis ([0,1,0,1]);
end

axis([0 1 0 1], "square")

xlabel ('\varphi_{21}')
ylabel ('\varphi_{31}')

%print -dsvg neuronPlot.svg

