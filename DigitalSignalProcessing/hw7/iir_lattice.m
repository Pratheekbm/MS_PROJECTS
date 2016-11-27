function y = iir_lattice(s,k1,k2,v1,v2,v3,G)

len = length(s);
f1 = zeros(1, len);
f2 = zeros(1, len);
f3 = zeros(1, len);
g1 = zeros(1, len);
g2 = zeros(1, len);
g3 = zeros(1, len);
y  = zeros(1, len);

f3(1) = G * s(1);
g3(1) = k2 * f2(1);
f2(1) = f3(1);
g2(1) = k1 * f1(1);
f1(1) = f2(1);
g1(1) = f1(1);
y(1)  = v1 * g1(1) + v2 * g2(1) + v3 * g3(1);
    
for i = 2:len
    f3(i) = G * s(i);
    f2(i) = f3(i) - k2 * g2(i - 1);
    f1(i) = f2(i) - k1 * g1(i - 1);
    
    g3(i) = k2 * f2(i) + g2(i - 1);
    g2(i) = k1 * f1(i) + g1(i - 1);
    g1(i) = f1(i);
    
    y(i)  = v1 * g1(i) + v2 * g2(i) + v3 * g3(i);
end































