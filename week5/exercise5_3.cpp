/* 练习5-3 高斯分布加权的高斯平滑滤波 */
#include <iostream>
#include <opencv2/opencv.hpp>
#define ksize 11         //卷积尺寸
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;

    cap.open(0);

    if(!cap.isOpened()) //检查是否能打开本地摄像头
    {
        std::cout << "不能打开视频文件" << std::endl;
        return -1;
    }

    while(1)
    {
        cv::Mat srcMat;
        cv::Mat dstMat;
        bool rSucess = cap.read(srcMat);
        srcMat.copyTo(dstMat);
        if(!rSucess)
        {
            std::cout << "不能从视频文件中读取帧" << std::endl;
            break;
        }
        else
        {
            GaussianBlur(srcMat, dstMat, Size(ksize,ksize), 3, 3, BORDER_DEFAULT);      //高斯平滑滤波
            cv::imshow("srcMat", srcMat);
            cv::imshow("dstMat", dstMat);
        }
        waitKey(30);
    }

    return 0;
}
