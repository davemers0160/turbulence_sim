#ifndef _MOTION_COMPENSTATE_H_
#define _MOTION_COMPENSTATE_H_

#include <cstdint>
#include <cmath>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>



static void meshgrid(const cv::Range& xgv, const cv::Range& ygv,
    cv::Mat& X, cv::Mat& Y)
    //const cv::Mat& xgv, const cv::Mat& ygv,
    //cv::Mat1i& X, cv::Mat1i& Y)
{
    std::vector<int> t_x, t_y;
    for (int i = xgv.start; i <= xgv.end; ++i) 
        t_x.push_back(i);

    for (int i = ygv.start; i <= ygv.end; ++i) 
        t_y.push_back(i);

    cv::repeat(xgv.reshape(1, 1), ygv.total(), 1, X);
    cv::repeat(ygv.reshape(1, 1).t(), 1, xgv.total(), Y);
}


/*
function g = MotionCompensate(img0, MVx, MVy, pel)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Integer pixel motion compensation
%
% g = reconstruct(img0, MVx, MVy, pel)
% constructs a motion compensated frame of img0 according to the motion
% vectors specified by MVx and MVy
%
%
% Stanley Chan
% 29 Apr, 2010
% 10 Feb, 2011
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
img = imresize(img0, 1/pel, 'bilinear');
BlockSize  = floor(size(img,1)/size(MVx,1));
[m n C]    = size(img);
M          = floor(m/block_size)*BlockSize;
N          = floor(n/block_size)*BlockSize;
f          = img(1:M, 1:N, 1:C);
g          = zeros(M, N, C);
MVxmap = imresize(MVx, BlockSize);
MVymap = imresize(MVy, BlockSize);
Dx = round(MVxmap*(1/pel));
Dy = round(MVymap*(1/pel));
[xgrid ygrid] = meshgrid(1:N, 1:M);
X = min(max(xgrid+Dx, 1), N);
Y = min(max(ygrid+Dy, 1), N);
idx = (X(:)-1)*M + Y(:);
for coloridx = 1:C
    fc = f(:,:,coloridx);
    g(:,:,coloridx) = reshape(fc(idx), M, N);
end
g = imresize(g, pel);
*/

cv::Mat motion_compensate(cv::Mat &src, cv::Mat MVx, cv::Mat MVy, double pel)
{
    cv::Mat tmp;
    cv::resize(src, tmp, Size(), 1.0/pel, 1.0/pel, cv::INTER_LINEAR);

    uint32_t img_h = tmp.rows;
    uint32_t img_w = tmp.cols;

    int32_t block_size = std::floor(img_h / (double)MVx.rows);

    int32_t M = std::floor(img_h / (double)block_size) * block_size;
    int32_t N = std::floor(img_w / (double)block_size) * block_size;

    cv::Mat f(tmp, cv::Rect(0, 0, N, M));

    cv::Mat g = cv::Mat::zeros(M, N, src.type());



}   // end of motion_compensate


#endif  // _MOTION_COMPENSTATE_H_
