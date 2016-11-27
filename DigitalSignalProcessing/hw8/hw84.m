% (a) Calculation of HPF co-efficients from LPF
alp = 0.1755;

a1 = conv([1 alp],[1 alp]);
a1 = conv(a1,[1 alp]);
a1 = conv(a1,[1 alp]);
a2 = 0.0803 * a1;

b1 = conv([1 alp],[1 alp]);
b1 = conv(b1,[1 alp]);
b1 = conv(b1,[alp 1]);
b2 = b1 * -0.1089;
b1 = b1 * 1.4655;

c1 = conv([1 alp],[1 alp]);
c1 = conv(c1,[alp 1]);
c1 = conv(c1,[alp 1]);
c2 = c1 * 0.1666;
c1 = c1 * 1.7272;

d1 = conv([1 alp],[alp 1]);
d1 = conv(d1,[alp 1]);
d1 = conv(d1,[alp 1]);
d2 = d1 * -0.1089;
d1 = d1 * 0.9687;

e1 = conv([alp 1],[alp 1]);
e1 = conv(e1,[alp 1]);
e1 = conv(e1,[alp 1]);
e2 = e1 * 0.0803;
e1 = e1 * 0.3187;

A = a1 + b1 + c1 + d1 + e1;
B = a2 + b2 + c2 + d2 + e2;
A
B
B = B/A(1);
A = A/A(1);

%(b) Verifying the co-efficients using ellip

[B1, A1] = ellip(4,1,34,0.7,'high');

figure(1)
freqz(B,A);
title('Magnitude and Phase response of the HPF with wc = 0.7, manually')

figure(2)
freqz(B1,A1);
title('Magnitude and Phase response of the HPF with wc = 0.7, using matlab ellip')