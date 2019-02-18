function match_test_fahmi(refImage, inputImage)
 
close all;
clear;
 
% surfnum = 1:30;
 
left_img  = imread(refImage);
right_img = imread(inputImage);
 
%SURF-128
[spixels_l,descr_l,sign_l,info_l] = surfpoints(left_img, surfoptions); 

%display the refImage and plot the keypoints
figure;
imshow(left_img);
hold on;
plot(spixels_l(1,:),spixels_l(2,:),'r*'); hold on

%SURF-128
[spixels_r,descr_r,sign_r,info_r] = surfpoints(right_img, surfoptions);


%display the inputImage and plot the keypoints
figure;
imshow(right_img);
hold on;
plot(spixels_r(1,:),spixels_r(2,:),'r*'); hold on
 
%Matching by SURF matching
matches = surfmatch(descr_l,descr_r);

surfnum = randi(size(matches,2),1,30);

% Show a figure with lines joining the accepted matches.
match_plot(left_img,right_img,spixels_l(:,matches(1,surfnum))',spixels_r(:,matches(2,surfnum))');

% Do not display the output image
%set(f, 'visible', 'off');


%figure;
imshow(left_img);
hold on;
surfplot(spixels_l(:,matches(1,surfnum)),info_l(:,matches(1,surfnum)));
 
%figure;
imshow(right_img);
hold on;
surfplot(spixels_r(:,matches(2,surfnum)),info_r(:,matches(2,surfnum)));

end