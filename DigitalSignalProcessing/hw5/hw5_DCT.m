%Loading sample data
x = sampdata;
figure(1);
stem(x);
xlabel('Time , n');
ylabel('Amplitude');
title('sampledata, x(n)')

dct_x = dct(x);
figure(2);
stem(dct_x);
xlabel('sample number');
ylabel('Magnitude');
title('DCT of x using dct()')


sym_x = padarray(x,[0,length(x)],'symmetric','post');
figure(3);
stem(sym_x);
xlabel('Time , n');
ylabel('Amplitude');
title('Symettric x')

sk = fft(sym_x);
range = exp(((-1i * pi)/(length(sk))) * (0.0:1:length(sk) - 1));
sk_2 = sk .* range;
sk_dct = sk_2(1:length(sk_2)/2);
figure(4)
stem(abs(dct_x - sk_dct));
xlabel('sample number');
ylabel('Magnitude');
title('Error between matlab DCT and DCT from notes')

sk_dct_matlab_correction = sk_dct * sqrt(2/length(sk_dct)) / 2;
sk_dct_matlab_correction(1) = sk_dct_matlab_correction(1)/sqrt(2);
figure(5)
stem(abs(dct_x - sk_dct_matlab_correction));
xlabel('sample number');
ylabel('Magnitude');
title('Error between matlab DCT and DCT from notes after matlab correction')
