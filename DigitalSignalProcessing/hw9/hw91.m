order = 100;
cutoff = 2/5;
freq = [0 cutoff/2 cutoff 1];
amp = [1 0.5 0 0];
samp_seq = fir2(order, freq, amp);
stem(samp_seq);