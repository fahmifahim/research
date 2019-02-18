function match_test()
 
close all;
clear;
 
% surfnum = 1:30;
 
left_img  = imread('./img1.png');
right_img = imread('./img1.png');
 
[spixels_l,descr_l,sign_l,info_l] = SurfPoints(rgb2gray(left_img));
 
figure;
imshow(left_img);
hold on;
plot(spixels_l(1,:),spixels_l(2,:),'r*'); hold on
 
[spixels_r,descr_r,sign_r,info_r] = SurfPoints(rgb2gray(right_img));
 
figure;
imshow(right_img);
hold on;
plot(spixels_r(1,:),spixels_r(2,:),'r*'); hold on
 
matches = surfmatch(descr_l,descr_r);
 
surfnum = randi(size(matches,2),1,30);
 
match_plot(left_img,right_img,spixels_l(:,matches(1,surfnum))',spixels_r(:,matches(2,surfnum))');
 
figure;
imshow(left_img);
hold on;
surfplot(spixels_l(:,matches(1,surfnum)),info_l(:,matches(1,surfnum)));
 
figure;
imshow(right_img);
hold on;
surfplot(spixels_r(:,matches(2,surfnum)),info_r(:,matches(2,surfnum)));
 
end