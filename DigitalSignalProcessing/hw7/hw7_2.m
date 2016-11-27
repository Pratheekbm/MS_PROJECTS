x = sampdata();

n = 1 : length(x);
s1 = iir_lattice(x, 0.4545, 0.5703, 1.2459, 0.7137, -1.0000, 1.0000);
s2 = iir_lattice(s1, -0.1963, 0.8052, -0.0475, -1.2347, 1.0000, 1.0000);
s3 = iir_lattice(s2, 0.8273, 0.8835, -0.1965, 0.3783, 1.0000, 1.0000);

figure(1)
plot(n, x)
title('x(n)');
xlabel('time, n');
ylabel('Maginitude');

figure(2)
plot(n, s3)
title('Filtered output of lattice, y(n)');
xlabel('time, n');
ylabel('Maginitude');

k1 = [0.4545, 0.5703];
v1 = [1.2459, 0.7137, -1.0000];
k2 = [-0.1963, 0.8052];
v2 = [-0.0475, -1.2347, 1.0000];
k3 = [0.8273, 0.8835];
v3 = [-0.1965, 0.3783, 1.0000];

[NUM,DEN] = latc2tf(k1,v1);
sm1 = filter(NUM,DEN,x);

[NUM,DEN] = latc2tf(k2,v2);
sm2 = filter(NUM,DEN,sm1);

[NUM,DEN] = latc2tf(k3,v3);
sm3 = filter(NUM,DEN,sm2);

figure(3)
plot(n, sm3);
title('Filtered output of matlab (filter), y(n)');
xlabel('time, n');
ylabel('Maginitude');

figure(4)
plot(n , (s3 - sm3));
title('Absolute error between lattice and matlab implementation');
xlabel('time, n');
ylabel('Maginitude');


