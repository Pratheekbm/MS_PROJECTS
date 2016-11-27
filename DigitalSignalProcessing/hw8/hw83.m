%(b) to verify if the co-efficients are same
[B,A] = butter(4, 0.3);

%(c) Plotting the response of the filter
a = [1.0000   -1.5705    1.2758   -0.4845    0.0762];
b = [0.0186    0.0742    0.1114    0.0742    0.0186];

figure(1)
freqz(b,a);
title('Magnitude and Phase response of the LPF with wc = 0.3, manually')

figure(2)
freqz(B,A);
title('Magnitude and Phase response of the LPF with wc = 0.3, using matlab')
