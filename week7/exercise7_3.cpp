/* 练习7-3 霍夫变换获取元件轮廓线段*/
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
    //霍夫变换获取元件轮廓线段方程
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(edgeMat, lines, 1, CV_PI / 180, 50, 0, 25);

    //绘制直线
    std::vector<cv::Vec4i>::iterator it = lines.begin();
    for( ; it != lines.end(); ++it)
    {
        cv::Point pt1, pt2;
        pt1.x = (*it)[0];
        pt1.y = (*it)[1];
        pt2.x = (*it)[2];
        pt2.y = (*it)[3];
        cv::line(dstMat, pt1, pt2, cv::Scalar(0, 255, 255), 1, CV_AA);
    }

    imshow("edge", edgeMat);
    imshow("dst", dstMat);
    waitKey(0);

    return 0;
}
