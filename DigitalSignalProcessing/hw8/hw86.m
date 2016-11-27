ws1 = 0.098;
wp1 = 0.1816;
wp2 = 0.8171;
ws2 = 0.9079;

delp = 0.15;
dels = 0.01;
mval = [0, 1, 0];
dev = [dels, delp, dels];
range = 0:1/512:1-1/512;

fedge = [ws1, wp1, wp2, ws2];
[N,Fo,Ao,W] = firpmord(fedge,mval,dev);
b = firpm(N,Fo,Ao,W);
figure()
freqz(b,1);
h = freqz(b,1);
figure()
plot(range,abs(h));
title('Magnitude response of the BPF firpm')
xlabel('Normalised Frequency, radians')
ylabel('Magnitude')
x = [0, 1];
y1 = [0.85, 0.85];
y2 = [1.15, 1.15];
y3 = [0.01, 0.01];
line(x, y1);
line(x, y2);
line(x, y3);


% adjusting trial and error, dev params
dev = [dels, 0.9174 * delp, dels];
[N,Fo,Ao,W] = firpmord(fedge,mval,dev);
b = firpm(N,Fo,Ao,W);
h = freqz(b,1);
figure()
plot(range,abs(h));
title('Magnitude response of the BPF firpm, post adjustment')
xlabel('Normalised Frequency, radians')
ylabel('Magnitude')
x = [0, 1];
y1 = [0.85, 0.85];
y2 = [1.15, 1.15];
y3 = [0.01, 0.01];
line(x, y1);
line(x, y2);
line(x, y3);