/* 练习5-2 均值滤波 */
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
            blur(srcMat, dstMat, Size(ksize,ksize), Point(-1,-1), BORDER_DEFAULT);      //均值滤波
            cv::imshow("srcMat", srcMat);
            cv::imshow("dstMat", dstMat);
        }
        waitKey(30);
    }

    return 0;
}
