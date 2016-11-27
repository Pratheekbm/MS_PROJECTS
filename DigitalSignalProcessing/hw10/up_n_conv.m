function [y] = up_n_conv(v,g)
n1 = 2 * length(v);
temp = zeros(1, n1);
temp(1, 1 : 2 : end) = v;
y = conv(temp, g);