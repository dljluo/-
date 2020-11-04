/* 练习6-1 第五章边缘提取 Canny算子 */
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
            Canny(srcMat, dstMat, 125, 150, 3, false);
            cv::imshow("srcMat", srcMat);
            cv::imshow("边缘", dstMat);

        }
        waitKey(30);
    }

    return 0;
}
