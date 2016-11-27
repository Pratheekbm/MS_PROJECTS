L = 30;
N = 400;
F1 = 200;
F2 = 220;
F3 = 250;

delta = 1;
point_dft = 2 ^ 16;
true_range = 2 * pi * (0:delta:N - 1) / N;
%true_range = pi*(0.0:delta:1.0);
signal_range = 0.0 : 1/1500 : 0.1;
x_t = cos(2 * pi * F1 * signal_range) + cos(2 * pi * F2 * signal_range) + cos(2 * pi * F3 * signal_range);
figure(1);
stem(x_t);
sampling_range = 2*pi*(0.0:1:N)/N;
w_r_n = exp(-1j * true_range * (L - 1)) .* sin(true_range * L / 2) ./ sin(true_range / 2);
figure(2);
plot(true_range, abs(w_r_n));
w_r_k = w_r_n(1:(2*pi/N)/delta:end);
figure(3);
stem(abs(w_r_k))
xlabel('w');
ylabel('Magnitude');
title('wh(k)')

figure(4);
x_rect_windowed = x_t(1:50);
x_rect_windowed_fft = fft(x_rect_windowed, point_dft);
stem(abs(x_rect_windowed_fft),'.');

L = 50;
w_r_n = exp(-1j * true_range * (L - 1)) .* sin(true_range * L / 2) ./ sin(true_range / 2);
figure(5);
plot(true_range, abs(w_r_n));

figure(6);
x_rect_windowed = x_t(1:100);
x_rect_windowed_fft = fft(x_rect_windowed, point_dft);
stem(abs(x_rect_windowed_fft),'.');

L = 100;
w_r_n = exp(-1j * true_range * (L - 1)) .* sin(true_range * L / 2) ./ sin(true_range / 2);
figure(7);
plot(true_range, abs(w_r_n));

figure(8);
x_rect_windowed = x_t(1:150);
x_rect_windowed_fft = fft(x_rect_windowed, point_dft);
stem(abs(x_rect_windowed_fft),'.');

L = 150;
w_r_n = exp(-1j * true_range * (L - 1)) .* sin(true_range * L / 2) ./ sin(true_range / 2);
figure(9);
plot(true_range, abs(w_r_n));

L = 30;
true_range1 = true_range;
w_h_n1 = 0.5 * exp(-1j * true_range1 * (L - 1)) .* sin(true_range1 * L / 2) ./ sin(true_range1 / 2);
true_range2 = true_range - (2 * pi / (L - 1));
w_h_n2 = 0.25 * exp(-1j * true_range2 * (L - 1)) .* sin(true_range2 * L / 2) ./ sin(true_range2 / 2);
true_range3 = true_range + (2 * pi / (L - 1));
w_h_n3 = 0.25 * exp(-1j * true_range3 * (L - 1)) .* sin(true_range3 * L / 2) ./ sin(true_range3 / 2);

w_h_n = w_h_n1 - w_h_n2 - w_h_n3;
figure(10);
plot(true_range, abs(w_h_n));
