N = 61;
M = 0.5 * (N - 1);
k1 = 0:12;
k2 = 14:30;

th = -1i * 2* pi * M * k1 / N;
h = exp(th);
h(14) = 0.45 * exp (-1i * 2* pi * M * 13 / N);
h(15 : 31) = 0.0;
h(32 : 61) = fliplr(conj(h(2:31)));
b = real(ifft(h));
a = 1;
range = pi * (0:1/511:1);
HS = freqz(b, a, range);

figure(1)
freqz(b);
title('Magnitude,phase response of filter from Frequency Sampling method');

