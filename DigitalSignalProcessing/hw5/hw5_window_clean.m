%INITIALISATION
L = 30;
N = 400;
F1 = 200;
F2 = 220;
F3 = 250;
Fs = 1500;
N_point_DFT = 2 ^ 16;

k = 0 : N - 1;
w = 2 * pi * k / N;

%Rectangular window Spectrum
window_r_k = exp(-0.5j * w * (L - 1)) .* sin(w * L / 2) ./ sin(w / 2);
figure(1);
subplot(2,1,1);
plot(w,abs(window_r_k));
title('Rectangular window Magnitude plot, L = 30');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_r_k));
title('Rectangular window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

%Hanning Window Spectrum
w1 = w;
window_h_k1 = 0.5 * exp(-0.5j * w1 * (L - 1)) .* sin(0.5 * w1 * L) ./ sin(0.5 * w1);
w2 = w - (2 * pi / (L - 1));
window_h_k2 = 0.25 * exp(-0.5j * w2 * (L - 1)) .* sin(0.5 * w2 * L) ./ sin(0.5 * w2);
w3 = w + (2 * pi / (L - 1));
window_h_k3 = 0.25 * exp(-0.5j * w3 * (L - 1)) .* sin(0.5 * w3 * L) ./ sin(0.5 * w3);
window_h_k = window_h_k1 - window_h_k2 - window_h_k3;
figure(2);
subplot(2,1,1);
plot(w,abs(window_h_k));
title('Hanning window Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_h_k));
title('Hanning window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

%Input Signal
t = 0.0 : 1/Fs : 1;
x_n = cos(2 * pi * F1 * t) + cos(2 * pi * F2 * t) + cos(2 * pi * F3 * t);


% Rectangular windowing on x(n) for different window lengths
% L = 50
window_length = 50;
window_r_n = ones([1, window_length]);
windowed_x_n = window_r_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(3);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Rectangular window on x(n), L = 50, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
window_r_k = exp(-0.5j * w * (L - 1)) .* sin(w * L / 2) ./ sin(w / 2);
figure(4);
subplot(2,1,1);
plot(w,abs(window_r_k));
title('Rectangular window Magnitude plot, L = 50');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_r_k));
title('Rectangular window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

% L=100
window_length = 100;
window_r_n = ones([1, window_length]);
windowed_x_n = window_r_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(5);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Rectangular window on x(n), L = 100, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
window_r_k = exp(-0.5j * w * (L - 1)) .* sin(w * L / 2) ./ sin(w / 2);
figure(6);
subplot(2,1,1);
plot(w,abs(window_r_k));
title('Rectangular window Magnitude plot, L = 100');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_r_k));
title('Rectangular window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

% L = 150
window_length = 150;
window_r_n = ones([1, window_length]);
windowed_x_n = window_r_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(7);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Rectangular window on x(n), L = 150, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
window_r_k = exp(-0.5j * w * (L - 1)) .* sin(w * L / 2) ./ sin(w / 2);
figure(8);
subplot(2,1,1);
plot(w,abs(window_r_k));
title('Rectangular window Magnitude plot, L = 150');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_r_k));
title('Rectangular window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');



% Hanning windowing on x(n), for different values of L
% L = 50
window_length = 50;
n = 0 : window_length - 1;
hanning = 0.5 * (1 - cos(2 * pi * n / (window_length - 1)));
window_h_n = ones([1, window_length]) .* hanning;
windowed_x_n = window_h_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(9);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Hanning window on x(n), L = 50, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
w1 = w;
window_h_k1 = 0.5 * exp(-0.5j * w1 * (L - 1)) .* sin(0.5 * w1 * L) ./ sin(0.5 * w1);
w2 = w - (2 * pi / (L - 1));
window_h_k2 = 0.25 * exp(-0.5j * w2 * (L - 1)) .* sin(0.5 * w2 * L) ./ sin(0.5 * w2);
w3 = w + (2 * pi / (L - 1));
window_h_k3 = 0.25 * exp(-0.5j * w3 * (L - 1)) .* sin(0.5 * w3 * L) ./ sin(0.5 * w3);
window_h_k = window_h_k1 - window_h_k2 - window_h_k3;
figure(10);
subplot(2,1,1);
plot(w,abs(window_h_k));
title('Hanning window Magnitude plot, L = 50');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_h_k));
title('Hanning window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

% L = 100
window_length = 100;
n = 0 : window_length - 1;
hanning = 0.5 * (1 - cos(2 * pi * n / (window_length - 1)));
window_h_n = ones([1, window_length]) .* hanning;
windowed_x_n = window_h_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(11);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Hanning window on x(n), L = 100, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
w1 = w;
window_h_k1 = 0.5 * exp(-0.5j * w1 * (L - 1)) .* sin(0.5 * w1 * L) ./ sin(0.5 * w1);
w2 = w - (2 * pi / (L - 1));
window_h_k2 = 0.25 * exp(-0.5j * w2 * (L - 1)) .* sin(0.5 * w2 * L) ./ sin(0.5 * w2);
w3 = w + (2 * pi / (L - 1));
window_h_k3 = 0.25 * exp(-0.5j * w3 * (L - 1)) .* sin(0.5 * w3 * L) ./ sin(0.5 * w3);
window_h_k = window_h_k1 - window_h_k2 - window_h_k3;
figure(12);
subplot(2,1,1);
plot(w,abs(window_h_k));
title('Hanning window Magnitude plot, L = 100');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_h_k));
title('Hanning window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

% L = 150
window_length = 150;
n = 0 : window_length - 1;
hanning = 0.5 * (1 - cos(2 * pi * n / (window_length - 1)));
window_h_n = ones([1, window_length]) .* hanning;
windowed_x_n = window_h_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(13);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Hanning window on x(n), L = 150, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
w1 = w;
window_h_k1 = 0.5 * exp(-0.5j * w1 * (L - 1)) .* sin(0.5 * w1 * L) ./ sin(0.5 * w1);
w2 = w - (2 * pi / (L - 1));
window_h_k2 = 0.25 * exp(-0.5j * w2 * (L - 1)) .* sin(0.5 * w2 * L) ./ sin(0.5 * w2);
w3 = w + (2 * pi / (L - 1));
window_h_k3 = 0.25 * exp(-0.5j * w3 * (L - 1)) .* sin(0.5 * w3 * L) ./ sin(0.5 * w3);
window_h_k = window_h_k1 - window_h_k2 - window_h_k3;
figure(14);
subplot(2,1,1);
plot(w,abs(window_h_k));
title('Hanning window Magnitude plot, L = 150');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_h_k));
title('Hanning window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');

% L = 200
window_length = 200;
n = 0 : window_length - 1;
hanning = 0.5 * (1 - cos(2 * pi * n / (window_length - 1)));
window_h_n = ones([1, window_length]) .* hanning;
windowed_x_n = window_h_n .* x_n(1 : window_length);
fft_windowed_x_n = fft(windowed_x_n, N_point_DFT);
figure(15);
plot((0 : Fs / N_point_DFT : Fs/2 - 1/N_point_DFT) ,abs(fft_windowed_x_n(1:length(fft_windowed_x_n)/2)));
title('Hanning window on x(n), L = 200, Magnitude plot');
xlabel('Normalized frequency (radians)');
ylabel('Magnitude');
L = window_length;
w1 = w;
window_h_k1 = 0.5 * exp(-0.5j * w1 * (L - 1)) .* sin(0.5 * w1 * L) ./ sin(0.5 * w1);
w2 = w - (2 * pi / (L - 1));
window_h_k2 = 0.25 * exp(-0.5j * w2 * (L - 1)) .* sin(0.5 * w2 * L) ./ sin(0.5 * w2);
w3 = w + (2 * pi / (L - 1));
window_h_k3 = 0.25 * exp(-0.5j * w3 * (L - 1)) .* sin(0.5 * w3 * L) ./ sin(0.5 * w3);
window_h_k = window_h_k1 - window_h_k2 - window_h_k3;
figure(16);
subplot(2,1,1);
plot(w,abs(window_h_k));
title('Hanning window Magnitude plot, L = 200');
xlabel('Normalized frequency (radians)');
ylabel('Maginitude');
subplot(2,1,2);
plot(w,angle(window_h_k));
title('Hanning window Phase plot');
xlabel('Normalized frequency (radians)');
ylabel('Phase');
