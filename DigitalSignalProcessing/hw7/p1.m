for k = 0:12
    hd1(k+1) = 1
end
hd1(14) = 0.9
for k = 14:30
    hd1(k+1) = 0
end
mp1 = length(hd1)
M = mp1 - 1;
N = 2*M + 1
Np1 = N + 1;
t1 = 0:M;
s = exp(-j*2*pi*M*t1/N); % Delay
hw = s.*hd1;
for k1 = 2:mp1
	k2 = N - k1 + 2;
	hw(k2) = conj(hw(k1));
end
b = real(ifft(hw));
figure(1)
freqz(b)
h = freqz(b)
hmag = abs(h)
