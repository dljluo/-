/* 练习5-4边缘提取 */
#include <iostream>
#include <opencv2/opencv.hpp>
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
        cv::Mat dstMatX, dstMatY;
        bool rSucess = cap.read(srcMat);
        srcMat.copyTo(dstMatX);
        srcMat.copyTo(dstMatY);
        if(!rSucess)
        {
            std::cout << "不能从视频文件中读取帧" << std::endl;
            break;
        }
        else
        {
            Sobel(srcMat, dstMatX, CV_8UC1, 1, 0, 3);       //提取水平方向上的边缘
            Sobel(srcMat, dstMatY, CV_8UC1, 0, 1, 3);       //提取竖直方向上的边缘
            cv::imshow("srcMat", srcMat);
            cv::imshow("X方向边缘", dstMatX);
            cv::imshow("Y方向边缘", dstMatY);
        }
        waitKey(30);
    }

    return 0;
}
