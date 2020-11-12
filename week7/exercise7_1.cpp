/* 练习7-1 不自动裁剪的图像旋转 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cv::Mat srcMat;             //原图像
    cv::Mat dstMatA,dstMatB;    //输出图像
    //读取原图像
    srcMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\orilena.png", 1);
    if(srcMat.empty()) return -1;

    float angle = -10.0;//旋转角度-40°
    float scale = 1;    //缩放比例
    //获取旋转中心
    cv::Point2f center(srcMat.cols/2.0, srcMat.rows/2.0);
    //获取外接四边形
    cv::Rect bbox = cv::RotatedRect(center, srcMat.size(), angle).boundingRect();

    /* A类变换：旋转后不改变原图尺寸，但输出图像变大 */
    //获取变换矩阵
    cv::Mat rotA = cv::getRotationMatrix2D(center, angle, scale);
    //调整仿射矩阵参数（改变中心坐标）
    rotA.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rotA.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    //仿射变换
    cv::warpAffine(srcMat, dstMatA, rotA, bbox.size());

    /* B类变换:旋转后改变原图尺寸，但输出图像尺寸与原图一样*/
    scale = srcMat.cols * 1.0 / bbox.width;
    cv::Mat rotB = cv::getRotationMatrix2D(center, angle, scale);
    cv::warpAffine(srcMat, dstMatB, rotB, srcMat.size());

    //显示原图像和输出图像
    imshow("src", srcMat);
    imshow("旋转后不改变原图尺寸，但输出图像变大", dstMatA);
    imshow("旋转后改变原图尺寸，但输出图像尺寸与原图一样", dstMatB);
    waitKey(0);

    return 0;
}
