/* 练习6-2 旋转与缩放 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cv::Mat srcMat;
    cv::Mat dstMat;

    srcMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\coin.jpg", 1);
    if(srcMat.empty()) return -1;

    //旋转-40°，缩放尺寸为
    float angle = -10.0, scale = 1;
    //旋转中心为图像中心
    cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
    //获得变换矩阵
    const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

    cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

    cv::imshow("src", srcMat);
    cv::imshow("dst", dstMat);
    cv::waitKey(0);

    return 0;
}
