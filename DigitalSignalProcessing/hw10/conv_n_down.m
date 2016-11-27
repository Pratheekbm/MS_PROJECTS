function [v] = conv_n_down(x,h)
temp = conv(x,h);
v = temp(1,1:2:end);