% num = match(image1, image2)
%
% This function reads two images, finds their SIFT features, and
%   displays lines connecting the matched keypoints.  A match is accepted
%   only if its distance is less than distRatio times the distance to the
%   second closest match.
% It returns the number of matches displayed.
%
% Example: match('scene.pgm','book.pgm');

function num = match(image1, image2, forLoop, path)

% Find SIFT keypoints for each image
[im1, des1, loc1] = sift(image1);
[im2, des2, loc2] = sift(image2);


% For efficiency in Matlab, it is cheaper to compute dot products between
%  unit vectors rather than Euclidean distances.  Note that the ratio of 
%  angles (acos of dot products of unit vectors) is a close approximation
%  to the ratio of Euclidean distances for small angles.
%
% distRatio: Only keep matches in which the ratio of vector angles from the
%   nearest to second nearest neighbor is less than distRatio.
distRatio = 0.6;   

% For each descriptor in the first image, select its match to second image.
des2t = des2';                          % Precompute matrix transpose
for i = 1 : size(des1,1)
   dotprods = des1(i,:) * des2t;        % Computes vector of dot products
   [vals,indx] = sort(acos(dotprods));  % Take inverse cosine and sort results

   % Check if nearest neighbor has angle less than distRatio times 2nd.
   if (vals(1) < distRatio * vals(2))
      match(i) = indx(1);
   else
      match(i) = 0;
   end
end

% Create a new image showing the two images side by side.
im3 = appendimages(im1,im2);

% Show a figure with lines joining the accepted matches.
f = figure('Position', [100 100 size(im3,2) size(im3,1)]);

% Do not display the output image
set(f, 'visible', 'off');

colormap('gray');
imagesc(im3);
hold on;
cols1 = size(im1,2);

for i = 1: size(des1,1)
  if (match(i) > 0)
    %line([loc1(i,2) loc2(match(i),2)+cols1], ...
    %     [loc1(i,1) loc2(match(i),1)], 'Color', 'c');
    plot([loc1(i,2) loc2(match(i),2)+cols1], ...
        [loc1(i,1) loc2(match(i),1)], 'Color', 'r', 'LineWidth', 2);
  end
end
hold off;
num = sum(match > 0);
fprintf('Found %d matches.\n', num);


%Save output images
outputImage = sprintf('%s%03d.jpg', path, forLoop);
saveas(f, outputImage, 'jpg');

% Close the "do not display output image"
close(f);
%imwrite(im3, outputImage, 'JPEG');

%Write output matches points into text file
%ConditionA vs Condition A
%file1_matches = fopen('C:/atad/Research/experiment/SIFT/result/matches_A_A.txt', 'a');

%ConditionA vs Condition D
%file1_matches = fopen('C:/atad/Research/experiment/SIFT/result/matches_A_D.txt', 'a');
file1_matches = fopen('c:/images/comparison/SIFT_matches.txt', 'a');

%ConditionA vs Condition H
%file1_matches = fopen('C:/atad/Research/experiment/SIFT/result/matches_A_H.txt', 'a');

fprintf(file1_matches, '%d\r\n', num);
fclose(file1_matches);





