S = 63412; %Number_of_samples
N = 1024; %Block Size
M = 98; %Filter coefficient length
L = N - M + 1 ;
% = 927, number of data length taken for every block
% Also number of zeros to be padded to filter

filter_padded = padarray(filter,[0 (N - M + 1)],0,'post');
ft1 = fft(filter_padded);

block_padded = padarray(block,[0 (M - 1)],0,'post');
ft2 = fft(block_padded);

y(1:N) = ft1 .* ft2;

y(L:L + n - 1) = y(L:L + n) + ft1 .* ft2;