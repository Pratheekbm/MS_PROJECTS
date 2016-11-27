function [v001, v01, v10, v11] = noise_reducer(v001, v01, v10, v11, beta001, beta01, beta10, beta11)
for i = 1:1:length(v001)
    if abs(v001(i)) < beta001
        v001(i) = 0;
    end
end

for i = 1:1:length(v01)
    if abs(v01(i)) < beta01
        v01(i) = 0;
    end
end

for i = 1:1:length(v10)
    if abs(v10(i)) < beta10
        v10(i) = 0;
    end
end

for i = 1:1:length(v11)
    if abs(v11(i)) < beta11
        v11(i) = 0;
    end
end