clear;
clc;
base='../../../dataset/';
% Subject 1
% train_sub
sadl1 = load([base 'S1-ADL1.dat']);
sadl2 = load([base 'S1-ADL2.dat']);
sadl3 = load([base 'S1-ADL3.dat']);
sdrill = load([base 'S1-Drill.dat']);
% test
sadl4 = load([base 'S1-ADL4.dat']);
sadl5 = load([base 'S1-ADL5.dat']);

[train_sub1,test_sub1]=tarrange(3,sadl1,sadl2,sadl3,sadl4,sadl5);
selectedCol = [1:37];
learning=[246,248];
HL_act=245;

%% Rename the rows 246 and 248 and delete 0 in them
% temp = zeros(1,size(train_sub1,2));
% for i = 1:length(train_sub1)
%     if((train_sub1(i,248) ~= 0))
%         temp(length(temp)+1,:) = train_sub1(i,:);
%     end
% end
% 
% train_sub1 = temp;

% for i = 1:length(train_sub1)    
%     if ((train_sub1(i,246) == 0))
%         train_sub1(i,246) = 1;
%     else
%         train_sub1(i,246) = train_sub1(i,246) - 200 + 1;
%     end
%     
%     if (train_sub1(i,248) == 0)
%         train_sub1(i,248) = 1;
%     else        
%         train_sub1(i,248) = train_sub1(i,248) - 400 + 1;
%     end   
% end
% 
% temp = zeros(1,size(test_sub1,2));
% for i = 1:length(test_sub1)
%     if((test_sub1(i,248) ~= 0))
%         temp(length(temp)+1,:) = test_sub1(i,:);
%     end
% end
% 
% test_sub1 = temp;
% 
% for i = 1:length(test_sub1)    
%     if ((test_sub1(i,246) == 0))
%         test_sub1(i,246) = 1;
%     else
%         test_sub1(i,246) = test_sub1(i,246) - 200 + 1;
%     end
%     
%     if (test_sub1(i,248) == 0)
%         test_sub1(i,248) = 1;
%     else        
%         test_sub1(i,248) = test_sub1(i,248) - 400 + 1;
%     end   
% end


%% Remove the rows corresponding to Null in the low level activity

% train_sub1=train_sub1(find(train_sub1(:,[248])~=0),:);
% train_sub1=train_sub1(find(train_sub1(:,[246])~=0),:);
% test_sub1=test_sub1(find(test_sub1(:,[248])~=0),:);
% test_sub1=test_sub1(find(test_sub1(:,[246])~=0),:);
%extract the sub set from the entire training data
HL_labels = train_sub1(:,HL_act);
HL_labels_test = test_sub1(:,HL_act);
train_sub = train_sub1(:,selectedCol);
learn_sub = train_sub1(:,learning);
test_sub = test_sub1(:,selectedCol);
test_sub_learn=test_sub1(:,learning);

% initialize the parameters
param=parameters;

%Remove the NaNs in the dataset either by repeating the previous value 'param.missingValue = R'
%or Deleting 'D' the NaNs 'param.missingValue=D'
[train_sub,testing] = missingValueHandler(train_sub,test_sub,param.missingValue);

%% Compensate for the missing lables in the test dataset when compared against the training set.
% data to be manipulated : test_learn_sub
% manipulator data: learn_sub
% find the missing class label in the test_learn_sub

% TODO : Dont replace labels

classes = unique(learn_sub(:,2));
test_classes = unique(test_sub_learn(:,2));
[missing] = ismember(classes,test_classes);
loc = find(missing == 0);
%replace the missing label with the label prior to it.
if(isempty(loc) ~= 1)
    for i=1:length(loc)
        if(loc(i)>1)
            learn_sub(classes(loc(i)) == learn_sub)=classes(loc(i)-1);
        else
            learn_sub(classes(loc(i)) == learn_sub)=classes(loc(i)+1);
        end
    end
end
clear classes;
clear test_classes;

%find the low level activities in column [246,248]
ngroups_left=length(unique(learn_sub(:,1)));
ngroups_right=length(unique(learn_sub(:,2)));


%% Extract feautures
% find the number of groups for the data to be classified into
ngroups=max(ngroups_left,ngroups_right);

% Separating various parts of the data
szData=size(train_sub);
szTest=size(testing);

%extract the features (mean) from the 500ms window with step size 250ms.
trainFeature=featureExtraction(train_sub,param.FX,1);
% Recalculating groups based on FX
if(ngroups_right>ngroups_left)
    trainFeatureLabel=featureExtraction(learn_sub(:,2),param.FX,2);
    classes=unique(learn_sub(:,2));
else
    trainFeatureLabel=featureExtraction(learn_sub(:,1),param.FX,2);
    classes=unique(learn_sub(:,1));
end

% % Feature extraction for test data
% testFeature=featureExtraction(test_sub,param.FX,1);
% for i=1:1:size(test_sub_learn,2)
%     testFeatureLabel(:,i)=featureExtraction(test_sub_learn(:,i),param.FX,2);
% end

testFeature=featureExtraction(test_sub,param.FX,1);

%% Check for the equality of the dimensions of test and train feature vectors
% TODO: Remove proper column
if(size(testFeature,2)>size(trainFeature,2))
    testFeature=testFeature(:,1:size(trainFeature,2));
elseif(size(testFeature,2)<size(trainFeature,2))
    trainFeature=trainFeature(:,1:size(testFeature,2));
end
% Recalculating groups based on FX
if(ngroups_right>ngroups_left)
    testFeatureLabel=featureExtraction(test_sub_learn(:,2),param.FX,2);
    test_classes=unique(test_sub_learn(:,2));
else
    testFeatureLabel=featureExtraction(test_sub_learn(:,1),param.FX,2);
    test_classes=unique(test_sub_learn(:,1));
end

%% Relabel the labels (201,202...) to (1,2...)
nTrain = size(trainFeatureLabel,1);
trainFeatureLabel_Indexed = zeros(nTrain,1);
for iClass = 1:ngroups
    trainFeatureLabel_Indexed(classes(iClass) == trainFeatureLabel)=iClass;
end

nTest = size(testFeatureLabel,1);
testFeatureLabel_Indexed = zeros(nTest,1);
for iClass = 1:ngroups
    testFeatureLabel_Indexed(test_classes(iClass) == testFeatureLabel)=iClass;
end

%% Classification
% Use one-vs-all logistic regression to classify and train the data
lambda=0.1;
[all_theta] = oneVsAll(trainFeature(:,2:end),trainFeatureLabel_Indexed,ngroups,lambda);

% pred_trainict for training set
pred_train=predictOneVsAll(all_theta, trainFeature(:,2:end));
fprintf('\nLow Level Training Set Accuracy: %f\n', mean(double(pred_train==trainFeatureLabel_Indexed))*100);


% pred_trainict for testing set
pred_test=predictOneVsAll(all_theta, testFeature(:,2:end));
fprintf('\nLow Level Testing Set Accuracy: %f\n', mean(double(pred_test==testFeatureLabel_Indexed))*100);

 %pred_train=trainFeatureLabel_Indexed;
 %pred_test=testFeatureLabel_Indexed;

%% Use the HMM to pred_trainict the higher activity labels (column 245) from the
% above classified lables. Using Baum-Welch algorithm to find the labels
% TODO LOW : Give A B
nu=rand(length(unique(sadl1(:,HL_act))),1);
nu=nu./sum(nu);
pred_train=pred_train';
nu=nu';
[Q, g, l] = HMMbaumwelch(pred_train, nu);

%% Calculate the (A,B,Pi) matrices to find the hidden states
HLTrain_FeatureLabel=featureExtraction(HL_labels,param.FX,2);
HLTest_FeatureLabel=featureExtraction(HL_labels_test,param.FX,2);

HL=unique(HL_labels);
HL_test=unique(HL_labels_test);

% find the priori probabilites pi
for i=1:length(HL)
    Pi(i)=sum(HLTrain_FeatureLabel==HL(i))/length(HLTrain_FeatureLabel);
end

% Relabel the labels (101,202...) to (1,2...)
HL_Train = size(HLTrain_FeatureLabel,1);
HLTrain_FeatureLabel_Indexed = zeros(HL_Train,1);
for iClass = 1:length(HL)
    HLTrain_FeatureLabel_Indexed(HL(iClass) == HLTrain_FeatureLabel)=iClass;
end

HL_Testing = size(HLTest_FeatureLabel,1);
HLTest_FeatureLabel_Indexed = zeros(HL_Testing,1);
for iClass = 1:length(HL_test)
    HLTest_FeatureLabel_Indexed(HL_test(iClass) == HLTest_FeatureLabel)=iClass;
end

% find the emission matrix B
ygroups = max(unique(pred_train));
B = zeros(ygroups,length(HL));
for i = 1:ygroups
    for j = 1:length(HL)
        loc = find(HLTrain_FeatureLabel_Indexed==j);
        temp = pred_train(loc);
        B(i,j) = sum(find(temp==i));
    end
end

B=B';
B=bsxfun(@rdivide,B,sum(B));


% B(1,1) = 1;
% B(2,1) = 1;
% B(3,1) = 1;
% B(4,1) = 1;
% B(5,1) = 1;
% B(6,1) = 1;

% B(1,12) = 100/400;
% B(2,12) = 00/400;
% B(3,12) = 100/400;
% B(4,12) = 100/400;
% B(5,12) = 00/400;
% B(6,12) = 100/400;
% 
% B(1,13) = 100/400;
% B(2,13) = 00/400;
% B(3,13) = 100/400;
% B(4,13) = 00/400;
% B(5,13) = 100/400;
% B(6,13) = 100/400;

%B=B';

HL_TF_A=HLTrain_FeatureLabel;
%HL_TF_A=featureExtraction(HLTrain_FeatureLabel,param.FX,2);
% find the transiton matrix A
A=zeros(length(HL),length(HL));
for i=1:length(HL)
    for j=1:length(HL)
        for k=1:length(HL_TF_A)-1
            if(HL_TF_A(k)==HL(i))
                if(HL_TF_A(k+1)==HL(j))
                    A(i,j)=A(i,j)+1;
                end
            end
        end
        A(i,j)=A(i,j)/sum(HL_TF_A(1:end-1)==HL(i));
    end
end

%[Q, g] = hmmestimate(pred_train, HLTrain_FeatureLabel_Indexed);

%% Get the most likely states from the forward propagation Viterbi algorithm
% This viterbi algorithm is designed to deal with discrete observation
% values (i.e. the scope of the observations is discrete.)
HL_pred_train= viterbi(1:length(HL),Pi',pred_train',Q,g);
HL_pred_test = viterbi(1:length(HL),Pi',pred_test',Q,g);
fprintf('\nHigh Level Training Set Accuracy: %f\n', mean(double(HL_pred_train'==HLTrain_FeatureLabel_Indexed))*100);
fprintf('\nHigh Level Test Set Accuracy: %f\n', mean(double(HL_pred_test'==HLTest_FeatureLabel_Indexed))*100);


