/* 练习2.调用本机摄像头 */
#include <iostream>
#include <opencv2\opencv.hpp>

#define CAP_PROR_FPS 5  //视频文件帧速率即帧数

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap;

    cap.open(0);        //打开本机第一个摄像头
    //cap.open("D:\\Programming\\CC++\\DigitalImageCode\\1.mp4"); //打开本地视频文件

    if(!cap.isOpened()) //检查是否能打开本地摄像头
    {
        std::cout << "不能打开视频文件" << std::endl;
        return -1;
    }

    double fps = cap.get(CAP_PROR_FPS);     //get(5)为帧速率，get(7)为总帧数
    std::cout << "fps" << fps << std::endl;
    while(1)
    {
        cv::Mat frame;
        bool rSucess = cap.read(frame);
        if(!rSucess)
        {
            std::cout << "不能从视频文件中读取帧" << std::endl;
            break;
        }
        else
        {
            cv::imshow("frame", frame);
        }
        waitKey(30);
    }

    return 0;
}
