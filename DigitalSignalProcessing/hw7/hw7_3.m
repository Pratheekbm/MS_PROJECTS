w1 = 3 * pi / 4;
w2 = pi / 4;
n1 = -30 : -1;
b2neg = (1 / pi) * (sin(w1 * (n1)) ./ (n1) - sin(w2 * (n1)) ./ (n1));
n2 = 1 : 30;
b2pos = (1 / pi) * (sin(w1 * (n2)) ./ (n2) - sin(w2 * (n2)) ./ (n2));
b20 = 1/2;
b2 = [b2neg b20 b2pos];
b3 = myblackman(61);
b4 = b2 .* b3;

range = pi * (0:1/511:1);
figure(1)
freqz(b4);
title('Magnitude,phase response of Bandpass, manual implm using Blackman');

N = 60;
wn = [1/4, 3/4];
w = blackman(61);
b5 = fir1(N,wn,'bandpass',w);

figure(2)
freqz(b5);
title('Magnitude,phase response of Bandpass, matlab implm using Blackman');

figure(3)
stem(b4 - b5)
title('Absolute error between manual and matlab filter coefficients');
xlabel('Normalized frequency (radians)');
ylabel('Absolute error');
