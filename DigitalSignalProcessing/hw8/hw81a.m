%Partial franctions
B = [1.5000 6.9050 1.8880];
A = [1 5.0900 5.7114];
[R,P,K] = residue(B,A);


%Plotting of Magnitude responses
w = 1 * pi * (0:1/100:1 - 1/100);
s =(1i*w);
Hs = (1.5 * s .* s + 6.9050 * s + 1.8880)./(s .* s + 5.0900 * s + 5.7114);

b1 = [0.6693 -2.4819 0.0050];
a1 = [1 -0.1661 0.0029];
h1 = freqz(b1,a1,w);

b2 = [1.0481 -0.3012 -0.3175];
a2 = [1 0.3055 -0.0066];
h2 = freqz(b2,a2,w);

figure(1);
plot(w,abs(h1),'--r',w,abs(h2),'-.b',w,abs(Hs),'-k');
