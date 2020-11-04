/* 练习6-4 投影变换 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cv::Mat dstMat;
    cv::Mat srcMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\2.jpg", 1);
    if(srcMat.empty()) return -1;

    //变换前四点坐标
    cv::Point2f pts1[] = {
                            cv::Point2f(150,150),
                            cv::Point2f(150,300),
                            cv::Point2f(350,300),
                            cv::Point2f(350,150) };
    //变换后三点坐标
    cv::Point2f pts2[] = {
                            cv::Point2f(200,150),
                            cv::Point2f(200,300),
                            cv::Point2f(340,270),
                            cv::Point2f(340,180) };
    //透视变换行列计算
    cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);
    //变换
    cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());

    cv::imshow("src", srcMat);
    cv::imshow("dst", dstMat);
    cv::waitKey(0);

    return 0;
}
