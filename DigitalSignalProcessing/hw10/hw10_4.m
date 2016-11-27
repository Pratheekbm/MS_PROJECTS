h0 = [-0.0106    0.0329    0.0308   -0.1870   -0.0280    0.6309    0.7148    0.2304];
h1 = [0.2304   -0.7148    0.6309    0.0280   -0.1870   -0.0308    0.0329    0.0106];
g0 = [0.2304    0.7148    0.6309   -0.0280   -0.1870    0.0308    0.0329   -0.0106];
g1 = [0.0106    0.0329   -0.0308   -0.1870    0.0280    0.6309   -0.7148    0.2304];

x = sampdata();
figure(1);
stem(x);
title('Stem plot of input x')
[v000, v001, v01, v10, v11] = decomp(x, h0, h1);
y = reconst(v000, v001, v01, v10, v11, g0, g1); figure(1);

figure(2);
stem(y);
title('Stem plot of output y')

load hwk10_signals.mat xn_prb2
xn_prb2_noisy = xn_prb2 + 0.1*randn(size(xn_prb2));

% First set of values
beta001 = 0.2;
beta01 = 0.13;
beta10 = 0.12;
beta11 = 0.12;

[v000, v001, v01, v10, v11] = decomp(xn_prb2_noisy, h0, h1);
[v001, v01, v10, v11] = noise_reducer(v001, v01, v10, v11, beta001, beta01, beta10, beta11);
y_beta1 = reconst(v000, v001, v01, v10, v11, g0, g1);

% Second set of values
beta001 = 1.9;
beta01 = 0.96;
beta10 = 0.95;
beta11 = 0.93;

[v000, v001, v01, v10, v11] = decomp(xn_prb2_noisy, h0, h1);
[v001, v01, v10, v11] = noise_reducer(v001, v01, v10, v11, beta001, beta01, beta10, beta11);
y_beta2 = reconst(v000, v001, v01, v10, v11, g0, g1);


% Third set of values
beta001 = 0.390;
beta01 = 0.390;
beta10 = 0.390;
beta11 = 0.353;

[v000, v001, v01, v10, v11] = decomp(xn_prb2_noisy, h0, h1);
[v001, v01, v10, v11] = noise_reducer(v001, v01, v10, v11, beta001, beta01, beta10, beta11);
y_beta3 = reconst(v000, v001, v01, v10, v11, g0, g1);

figure(3)
plot(xn_prb2)
title('plot of original signal')
figure(4)
plot(xn_prb2_noisy)
title('plot of noisy signal')
figure(5)
plot(y_beta1)
title('plot of first reconstructed signal')
figure(6)
plot(y_beta2)
title('plot of second reconstructed signal')
figure(7)
plot(y_beta3)
title('plot of third reconstructed signal')
