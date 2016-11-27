function [HLL] = BaumWelch(data,num_xlabels,iterations)

% BaumWelch for discrete observations case
num_ylabels=length(unique(data));


% A = {aij} = P(Xt=j|X(t-1)=i) Transition matrix from one hidden state
% to another
% B = {bj(yt)}; bj(yt) = P(Yt=yt|Xt=j) Emission matrix that has the
% information about the probability of an observation at instant t, given
% the hidden state assumes the value j
% pi = P(X1=i) Initial state distribution

A=zeros(num_xlabels,num_xlabels);
B=zeros(num_ylabels,num_xlabels);
pi=zeros(num_xlabels,1);

pi1 = normalise(rand(num_xlabels,1));
A1 = mk_stochastic(rand(num_xlabels,num_xlabels));
B1 = mk_stochastic(rand(num_ylabels,num_xlabels));

for i=1:iterations
   
    % Forward Procedure
    alpha(i,1)=pi1.*B1(:,1);
    
    alpha(j,t)=b(j,t)*(alpha(i,t)*A1(i,j))
    
    
end


end

