function surfplot(points,info)
%SURFPLOT plots SURF interest points returned from SURFPOINTS
%
%   SURFPLOT(POINTS,INFO) plots the interest points from the two arguments
%   returned from SURFPOINTS.
%
%   See also: SURFPOINTS
%
%   Petter Strandmark 2008

    colorline= {'r-','b-','c-','g-','m-'};
    phi = linspace(0,2*pi);
    x = cos(pi/2 + phi);
    y = sin(pi/2 + phi);
    bbox = [x 0; y 0];
       
    for k = 1:size(points,2)
        scale = info(1,k);
        %ori   = -info(3,k)*(2*pi/360);
        ori   = -info(3,k)*pi/180;
        
        R = [cos(ori) -sin(ori);sin(ori) cos(ori)];
        
        pbox = scale*R*bbox + points(:,k)*ones(1,size(bbox,2));
        hold on;
        %plot(pbox(1,:),pbox(2,:),'w-');
        plot(pbox(1,:),pbox(2,:),colorline{mod(k,5)+1});
    end
    
    
end