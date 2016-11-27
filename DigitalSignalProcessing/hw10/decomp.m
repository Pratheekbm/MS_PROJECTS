function [v000, v001, v01, v10, v11] = decomp(x, h0, h1)
temp = conv_n_down(x,h0);
temp1 = conv_n_down(temp,h0);
v000 = conv_n_down(temp1,h0);
v001 = conv_n_down(temp1,h1);
v01 = conv_n_down(temp,h1);
temp2 = conv_n_down(x,h1);
v10 = conv_n_down(temp2,h0);
v11 = conv_n_down(temp2,h1);
end