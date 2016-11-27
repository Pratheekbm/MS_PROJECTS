b = [0.1311   -0.2622    0.1311];
a = [1.0000    0.7478    0.2722];
figure(2)
freqz(b,a)
title('Magnitude and Phase response of the HPF with wc = 0.7')