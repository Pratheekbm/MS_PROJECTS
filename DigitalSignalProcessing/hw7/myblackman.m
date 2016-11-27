function wind = myblackman(n)
% wind = myblackman(n);
%
% This routine returns a Blackman window % of length n.
nmod = mod(n,2);
c = 2 * pi/(n - 1);
if (nmod == 1)
    m = fix(0.5 * (n - 1));
    k = -m : 1 : m;
    wind = 0.42 + 0.5 * cos(k * c) + 0.08 * cos(k * 2 * c);
elseif (nmod == 0)
    m = fix(0.5 * n);
    k = -m : 1 : (m - 1);
	k = k + 0.5;
    wind = 0.42 + 0.5 * cos(k * c) + 0.08 * cos(k * 2 * c);
end
return