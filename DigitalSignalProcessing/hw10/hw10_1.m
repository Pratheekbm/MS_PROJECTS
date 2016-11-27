clear();
clc();

a = -5;
b = 40;
c = -131;
d = 208;
ks_roots = roots([a b c d c b a]);

g0 = 1/32 * (poly([ ks_roots(2) ks_roots(3) ks_roots(4) ks_roots(5) -1 -1 -1]));
h0 = 1/64 * (poly([ks_roots(1) ks_roots(6) -1 -1 -1 -1 -1]));

h1 = zeros(1,length(h0));
g1 = zeros(1,length(h0));

for i = 1 : length(h0);
h1(i) = (-1)^(i-1) * g0(i);
g1(i) = (-1)^(i) * h0(i);
end;

figure(1)
freqz(h0);
title('h0');

figure(2)
freqz(g0);
title('g0');

figure(3)
freqz(h1);
title('h1');

figure(4)
freqz(g1);
title('g1');

t = 0.5*(conv(h0,g0)+conv(h1,g1));
figure(5)
freqz(t);
title('Distortion (t)');

w = 0:1/511:1;
figure(6);
plot(w,abs(freqz(h0)),w,abs(freqz(h1)));
title('h0 and h1 in same plot');

A = 0.5.*((g0.*(-g1))+(g1.*g0))

