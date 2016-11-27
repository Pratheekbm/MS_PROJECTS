function y = reconst(v000, v001, v01, v10, v11, g0, g1)
v000d = up_n_conv(v000,g0);
v001d = up_n_conv(v001,g1);
v000_001d = up_n_conv((v000d + v001d),g0);

v10d = up_n_conv(v01,g1);
a = up_n_conv(v000_001d + [zeros(1,(length(v000_001d) - length(v10d))/2) v10d zeros(1,(length(v000_001d) - length(v10d))/2)] , g0);

v10d = up_n_conv(v10,g0);
v11d = up_n_conv(v11,g1);

v10_11d = up_n_conv((v10d + v11d),g1);
y = a + [zeros(1,(length(a) - length(v10_11d))/2) v10_11d zeros(1,(length(a) - length(v10_11d))/2)];
end