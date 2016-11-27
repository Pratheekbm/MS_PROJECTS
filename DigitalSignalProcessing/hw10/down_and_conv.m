function [v] = conv_n_down(x,h)
a1 = conv(x,h);
v = a1(1,1:2:end);