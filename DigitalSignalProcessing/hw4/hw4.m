x = sampdata;
figure(1);
stem(x);
xlabel('Time , n');
ylabel('Amplitude');
title('sampledata, x(n)')

%Filter
order = 32;
ws = 0.749;
wc = 0.85*ws;
F = [0.0 wc ws 1.0];
A = [1.0 0.95 0.01 0.0];
b = firpm(order, F, A);
range = pi*(0.0:1/511:1.0);
H = freqz(b);

figure(2);
plot(range,abs(H))
xlabel('Normalized Frequency (radians)')
ylabel('Magnitude')
title('Frequency Response Plot')

figure(3)
plot(range,angle(H))
title('Phase Response Plot')
xlabel('Normalized Frequency (radians)')
ylabel('Phase')

y1 = conv(x,b);
figure(4)
stem(y1);
xlabel('Time , n');
ylabel('Amplitude');
title('y1(n)')

b_padded = padarray(b,[0 (length(x) - 1)],0,'post');
x_padded = padarray(x,[0 (length(b) - 1)],0,'post');
y2 = ifft( (fft(x_padded)) .* (fft(b_padded)) );
figure(5)
stem(y2);
xlabel('Time , n');
ylabel('Amplitude');
title('y2(n)')

figure(6)
stem(y2 - y1);
xlabel('Time , n');
ylabel('Amplitude');
title('Error between y2(n) and y1(n)')

