function [C,postNorm,mahal] = GausianClassify(dtest,dtrain,group,mode)
% this function is for the LDA and QDA classifiers
% The inputs are:
%   dtest: the test data set,  dtrain: the training dataset
%   group: the actual labels of training set,  mode: LDA or QDA
% The outputs are:
%   C: the predicted labels for the test set
%   postNorm: the normalized posterior probability
%   mahal: the log of the posterior probability

%dimensions of the dataset
[nTest nFeature] = size(dtest);
nTrain = size(dtrain,1);
%find the number of classes to be classified into
classes = unique(group);
nClass = length(classes);
%create a classifier array of the size of the training set to allocate a
%class for each sample (feature) in the dtrain.
iclassIndex = zeros(nTrain,1);

%relabel the exisiting labels (201,..213 or 401,..413) to (1,..13)
%accordingly
for iClass = 1:nClass
    iclassIndex(classes(iClass) == group)=iClass;
end

%create an empty array of NaNs
logpost = NaN(nTest,nClass);
switch mode
    case 'diaglinear',
        gmeans = NaN(nClass, nFeature);
        for k = 1:nClass
            %get the mean value of all the instances in dtrain that
            %correspond to a particular class. Get it for all such classes.
            gmeans(k,:) = mean(dtrain(group==classes(k),:),1);
        end
        % quantify how far each sample (corresponding to a class) is from the
        % mean value of that class. Do it for all those classes
        S = std(dtrain - gmeans(iclassIndex,:)) * sqrt((nTrain-1)./(nTrain-nClass));
        logDetSigma = 2*sum(log(S)); % avoid over/underflow
        for k = 1:nClass
            A=bsxfun(@times, bsxfun(@minus,dtest,gmeans(k,:)),1./S);
            logpost(:,k) = - .5*(sum(A .* A, 2) + logDetSigma);
        end
        [maxD Ci] = max(logpost,[],2);
        C = classes(Ci);
        P = exp(bsxfun(@minus,logpost(1:nTest,:),maxD(1:nTest)));
        sumP = nansum(P,2);
        postNorm = bsxfun(@times,P,1./(sumP));
        
        logpost = -logpost;
        mahal =  logpost;
    case 'diagquadratic',
        gmeans = NaN(nClass, nFeature);
        for k = 1:nClass
            gmeans(k,:) = mean(dtrain(group==classes(k),:),1);
        end
        logDetSigma = zeros(1,nClass);
        for k = 1:nClass
            S = std(dtrain(iclassIndex==k,:));
            logDetSigma(k) = 2*sum(log(S)); % avoid over/underflow
            % MVN relative log posterior density, by group, for each sample
            A=bsxfun(@times, bsxfun(@minus,dtest,gmeans(k,:)),1./S);
            logpost(:,k) = -.5*(sum(A .* A, 2) + logDetSigma(k));
        end
        [maxD Ci] = max(logpost,[],2);
        C = classes(Ci);
        P = exp(bsxfun(@minus,logpost(1:nTest,:),maxD(1:nTest)));
        sumP = nansum(P,2);
        postNorm = bsxfun(@times,P,1./(sumP));
        
        logpost = -logpost;
        mahal =  logpost;
end