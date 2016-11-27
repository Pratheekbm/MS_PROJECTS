% manual calculation
xk = [6 1.9289+9.4852i -4+6i 16.0711+7.4853i -2 16.0711-7.4853i -4-6i 1.9289-9.4852i];
figure(1);
stem(abs(xk));
xlabel('k')
ylabel('Magnitude')
title('Frequency Response Plot of X(k) manual calculation')

% matlab calculation
xn = [4 -6 1 2 -5 5 2 3];
figure(2);
stem(abs(fft(xn)));
xlabel('k')
ylabel('Magnitude')
title('Frequency Response Plot of X(k) matlab calculation')