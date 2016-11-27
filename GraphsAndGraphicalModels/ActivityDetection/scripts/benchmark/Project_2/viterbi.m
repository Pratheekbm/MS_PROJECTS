function [X] = viterbi(states,pi,observations,A,B)

% INPUT
% The observation space  O=\{o_1,o_2,\dots,o_N\},
% the state space  S=\{s_1,s_2,\dots,s_K\} ,
% a sequence of observations  Y=\{y_1,y_2,\ldots, y_T\}  such that  y_t==i  if the observation at time  t  is  o_i ,
% transition matrix  A  of size  K\cdot K  such that  A_{ij}  stores the transition probability of transiting from state  s_i  to state  s_j ,
% emission matrix  B  of size  K\cdot N  such that  B_{ij}  stores the probability of observing  o_j  from state  s_i ,
% an array of initial probabilities  \pi  of size  K  such that  \pi_i  stores the probability that  x_1 ==  s_i 

T=zeros(length(states),length(observations));

T(:,1) = pi.*B(:,observations(1));

for i = 2:length(observations)
    for j = 1:length(states)
        temp = T(:,(i-1)).*A(:,j)*B(j,observations(i));
        if max(temp>0)
            [val,loc] = max(temp) ;
            T(j,i) = val;  
        else
            T(j,i) = 0;
            %warning('This dataset is an asshole. Move on and get a life.');
        end
    end
    if(max(T(:,i))>0)
        T(:,i)=T(:,i)./max(T(:,i));
    else
        T(:,i)=0;
        warning('LOL dataset is an asshole. Move on and get a life.');
    end
        
end

[val1,loc1]=(max(T,[],1));
Z=val1;
X=loc1;

y=0;
end