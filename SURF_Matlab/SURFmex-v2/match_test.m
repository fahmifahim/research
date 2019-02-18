function match_test(refImage, inputImage, forLoop, path)
 
%close all;
%clear;
 
% surfnum = 1:30;
 
left_img  = imread(refImage);
right_img = imread(inputImage);
 
%[spixels_l,descr_l,sign_l,info_l] = surfpoints(rgb2gray(left_img));

%SURF-64 (default)
%[spixels_l,descr_l,sign_l,info_l] = surfpoints(left_img); 

%SURF-128
[spixels_l,descr_l,sign_l,info_l] = surfpoints(left_img, surfoptions); 

%fprintf('Reference image features: ');
%size(spixels_l)

%display the refImage and plot the keypoints
%figure;
%imshow(left_img);
%hold on;
%plot(spixels_l(1,:),spixels_l(2,:),'r*'); hold on
 
%[spixels_r,descr_r,sign_r,info_r] = surfpoints(rgb2gray(right_img));

%SURF-64 (default)
%[spixels_r,descr_r,sign_r,info_r] = surfpoints(right_img);

%SURF-128
[spixels_r,descr_r,sign_r,info_r] = surfpoints(right_img, surfoptions);
 
%fprintf('Input image features: ');
%size(spixels_r)

%display the inputImage and plot the keypoints
%figure;
%imshow(right_img);
%hold on;
%plot(spixels_r(1,:),spixels_r(2,:),'r*'); hold on
 
%Matching by SURF matching
%matches = surfmatch(descr_l,descr_r);

%SIFT matching method (David Lowe vl_ubcmatch)
[matches, scores] = vl_ubcmatch(descr_l,descr_r) ;

matchPercentage = size(scores, 2)/size(descr_l, 2) * 100;
fprintf('Matching score for image %d: %d/%d * 100 = %f\n', forLoop, size(scores, 2), size(descr_l, 2), matchPercentage);

%write #input features, #matching, matchingPercentage
matchingPercentage = fopen(sprintf('%smatchingPercentage.txt', path), 'a');
fprintf(matchingPercentage, '%d, %d, %f\r\n', size(descr_r, 2), size(scores, 2), matchPercentage);
fclose(matchingPercentage);

%surfnum = randi(size(matches,2),1,30);

% Show a figure with lines joining the accepted matches.
%f = match_plot(left_img,right_img,spixels_l(:,matches(1,surfnum))',spixels_r(:,matches(2,surfnum))');

% Do not display the output image
%set(f, 'visible', 'off');


%figure;
%imshow(left_img);
%hold on;
%surfplot(spixels_l(:,matches(1,surfnum)),info_l(:,matches(1,surfnum)));
 
%figure;
%imshow(right_img);
%hold on;
%surfplot(spixels_r(:,matches(2,surfnum)),info_r(:,matches(2,surfnum)));

%Save output images
%outputImage = sprintf('%s%03d.jpg', path, forLoop);
%saveas(f, outputImage, 'jpg');

% Close the "do not display output image"
%close(f);

end