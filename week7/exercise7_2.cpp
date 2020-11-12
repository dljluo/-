/* 练习7-2 霍夫变换获取元件两长边直线方程*/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    cv::Mat srcMat;
    cv::Mat dstMat;
    cv::Mat edgeMat;

    srcMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\exe7.jpg", 0);
    if(srcMat.empty()) return -1;
    dstMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\exe7.jpg", 1);
    if(dstMat.empty()) return -1;

    Canny(srcMat, edgeMat, 125, 250, 3, false);          //边缘提取
    //霍夫变换获取元件两长边直线方程
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edgeMat, lines, 1, CV_PI / 180, 120);

    //绘制直线
    std::vector<cv::Vec2f>::iterator it = lines.begin();
    for( ; it != lines.end(); ++it)
    {
        float rho = (*it)[0], theta = (*it)[1];
        cv::Point pt1, pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a*rho;
        double y0 = b*rho;
        pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
        pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
        pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
        pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
        cv::line(dstMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
    }

    imshow("edge", edgeMat);
    imshow("dst", dstMat);
    waitKey(0);

    return 0;
}
