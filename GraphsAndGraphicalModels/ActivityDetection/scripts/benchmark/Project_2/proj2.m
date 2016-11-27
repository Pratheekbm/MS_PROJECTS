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
selectedCol = 1:37;
learning = [246,248];
HL_act = 245;

%% Rename the rows 246 and 248 and delete 0 in them
temp = zeros(1,size(train_sub1,2));
for i = 1:length(train_sub1)
    if( (train_sub1(i,246) ~= 0) || (train_sub1(i,248) ~= 0))
        temp(length(temp)+1,:) = train_sub1(i,:);
    end
end

train_sub1 = temp;

for i = 1:length(train_sub1)    
    if ((train_sub1(i,246) == 0))
        train_sub1(i,246) = 1;
    else
        train_sub1(i,246) = train_sub1(i,246) - 200 + 1;
    end
    
    if (train_sub1(i,248) == 0)
        train_sub1(i,248) = 1;
    else        
        train_sub1(i,248) = train_sub1(i,248) - 400 + 1;
    end   
end

temp = zeros(1,size(test_sub1,2));
for i = 1:length(test_sub1)
    if( (test_sub1(i,246) ~= 0) || (test_sub1(i,248) ~= 0))
        temp(length(temp)+1,:) = test_sub1(i,:);
    end
end

test_sub1 = temp;

for i = 1:length(test_sub1)    
    if ((test_sub1(i,246) == 0))
        test_sub1(i,246) = 1;
    else
        test_sub1(i,246) = test_sub1(i,246) - 200 + 1;
    end
    
    if (test_sub1(i,248) == 0)
        test_sub1(i,248) = 1;
    else        
        test_sub1(i,248) = test_sub1(i,248) - 400 + 1;
    end   
end

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

%% Extract Features

%find the low level activities in column [246,248]
ngroups_left = length(unique(learn_sub(:,1)));
ngroups_right = length(unique(learn_sub(:,2)));

% Separating various parts of the data
szData = size(train_sub);
szTest = size(testing);

% extract the features (mean) from the 500ms window with step size 250ms.
trainFeature = featureExtraction(train_sub,param.FX,1);
testFeature = featureExtraction(test_sub,param.FX,1);

% Recalculating groups based on FX
if(ngroups_right > ngroups_left)
    trainFeatureLabel = featureExtraction(learn_sub(:,2),param.FX,2);
    classes = unique(learn_sub(:,2));
else
    trainFeatureLabel = featureExtraction(learn_sub(:,1),param.FX,2);
    classes = unique(learn_sub(:,1));
end



