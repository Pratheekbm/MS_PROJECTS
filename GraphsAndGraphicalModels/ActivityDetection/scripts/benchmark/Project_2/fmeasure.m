
for i=1:1:6
   state = i;
   idx = find(HLTrain_FeatureLabel_Indexed == state);
   idx_other = find(HLTrain_FeatureLabel_Indexed ~= state);
   est_idx = HL_pred_train(idx);
   other_idx = HL_pred_train(idx_other);
   w(i) = length(idx)/length(HLTrain_FeatureLabel_Indexed);
   tp(i) = length(find(est_idx==state));
   tn(i) = length(find(other_idx~=state));
   fp(i) = length(find(other_idx==state));
   fn(i) = length(find(est_idx~=state));
   if (tp(i)+fp(i))~=0
       precision(i)=tp(i)/(tp(i)+fp(i));
   else
       precision(i)=0;
   end
   if (tp(i)+fn(i))~=0
       recall(i)= tp(i)/(tp(i)+fn(i));
   else
       recall(i)=0;
   end
end
f_val=0;
for i=1:1:6
   if (precision(i)+recall(i))~=0
       f_val=f_val+ 2*w(i)*precision(i)*recall(i)/(precision(i)+recall(i));
   end
end
f_val;

% ROC plot
target=HLTrain_FeatureLabel_Indexed;
output=HL_pred_train;

p=ones(1,length(target));
targets = zeros(6,length(target));
outputs=zeros(6,length(output));
for i=0:5
  
  bb= (target-i)==0;
  targets(i+1,:)=(bb);
  clear bb
  
   bb= (output-i)==0;
  outputs(i+1,:)=(bb);
  clear bb
  
 end
for i=0:5
figure();
plotroc(targets(i+1,:), outputs(i+1,:));
str=sprintf('ROC plot for Class - %d',i+1);
title(str);
end
