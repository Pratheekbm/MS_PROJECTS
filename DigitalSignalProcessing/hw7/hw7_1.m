b = [0.0609 -0.3157 0.8410 -1.4378 1.7082 -1.4378 0.8410 -0.3157 0.0609];
a = [1.0 -0.8961 2.6272 -0.9796 2.1282 -0.0781 0.9172 0.0502 0.2602];
[sos, gain] = tf2sos(b, a);

k11 = sos(1,5)/(1 + sos(1,6));
k12 = sos(1,6);
v13 = sos(1,3);
v12 = sos(1,2) - ((k11 * k12 + k11) * sos(1,3));
v11 = sos(1,1) - v12 * k11 - v13 * k12;

k21 = sos(2,5)/(1 + sos(2,6));
k22 = sos(2,6);
v23 = sos(2,3);
v22 = sos(2,2) - ((k21 * k22 + k21) * sos(2,3));
v21 = sos(2,1) - v22 * k21 - v23 * k22;

k31 = sos(3,5)/(1 + sos(3,6));
k32 = sos(3,6);
v33 = sos(3,3);
v32 = sos(3,2) - ((k31 * k32 + k31) * sos(3,3));
v31 = sos(3,1) - v32 * k31 - v33 * k32;

k41 = sos(4,5)/(1 + sos(4,6));
k42 = sos(4,6);
v43 = sos(4,3);
v42 = sos(4,2) - ((k41 * k42 + k41) * sos(4,3));
v41 = sos(4,1) - v42 * k41 - v43 * k42;

