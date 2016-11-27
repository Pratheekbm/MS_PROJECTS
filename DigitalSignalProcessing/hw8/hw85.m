Fs = 20000;
wp = 2 * 7200/(20000);
ws = 2 * 8500/(20000);
rp = 1;
rs = 40;


[n1, wn1] = buttord(wp, ws, rp, rs);
[n2, wn2] = cheb1ord(wp, ws, rp, rs);
[n3, wn3] = cheb2ord(wp, ws, rp, rs);
[n4, wn4] = ellipord(wp, ws, rp, rs);

[b1, a1] = butter(n1, wp);
[b2, a2] = cheby1(n2, rp, wp);
[b3, a3] = cheby2(n3, rs, ws);
[b4, a4] = ellip(n4, rp, rs, wp);
figure(1)
freqz(b1,a1)
title('Magnitude and Phase response of the LPF with wp = 0.72, butter')

figure(2)
freqz(b2,a2)
title('Magnitude and Phase response of the LPF with wp = 0.72, cheby1')

figure(3)
freqz(b3,a3)
title('Magnitude and Phase response of the LPF with ws = 0.875, cheby2')

figure(4)
freqz(b4,a4)
title('Magnitude and Phase response of the LPF with wp = 0.72, ellip')