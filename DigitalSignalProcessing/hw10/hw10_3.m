clear();
clc();

h0 = fir1(40,0.25);
h1 = fir1(40,0.25,'high');
length_h0 = length(h0);
length_h1 = length(h1);

%Plotting h0 and h1ß
figure(1)
freqz(h0,1);
title('Magnitude and phase response h0');
figure(2)
freqz(h1,1);
title('Magnitude and phase response h1');
% Calculating h0(z2)
h0_z2 = zeros(1, 2 * length_h0);
k = 1 : 2 : length(h0_z2);
h0_z2(k) = h0;

% Calculating h0(z4)
h0_z4 = zeros(1, 4 * length_h1); 
k = 1 : 4 : length(h0_z4);
h0_z4(k) = h0;

% Calculating H1(z2)
h1_z2 = zeros(1,2 * length_h1);
k = 1 : 2 :length(h1_z2);
h1_z2(k) = h1;

% Calculating H1(z4)
h1_z4 = zeros(1, 4 * length_h1);
k = 1 : 4 : length(h1_z4);
h1_z4(k) = h1;

h0_prime = conv(conv(h0,h0_z2),h0_z4);
h1_prime = conv(conv(h0,h0_z2),h1_z4);
h2_prime = conv(h0,h1_z2);
h3_prime = conv(h1,h0_z2);
h4_prime = conv(h1,h1_z2);

figure(3)
freqz(h0_prime,1);
title('Magnitude and phase response h0`');
figure(4)
freqz(h1_prime,1);
title('Magnitude and phase response h1`');
figure(5)
freqz(h2_prime,1);
title('Magnitude and phase response h2`');
figure(6)
freqz(h3_prime,1);
title('Magnitude and phase response h3`');
figure(7)
freqz(h4_prime,1);
title('Magnitude and phase response h4`');

figure(8)
w = (0:0.1:51.1)*(1/100);
plot(w,abs(freqz(h0_prime)),w,abs(freqz(h1_prime)),w,abs(freqz(h2_prime)),w,abs(freqz(h3_prime)),w,abs(freqz(h4_prime)))
title('Magnitude response of all the analysis filters');
xlabel('Normalized frequency');
ylabel('Magnitude');