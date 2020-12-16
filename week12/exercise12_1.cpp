/**练习11-1 实现背景差分**/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())     //检查是否能打开摄像头
    {
        std::cout << "不能打开摄像头" << std::endl;
        return -1;
    }

    cv::Mat frame;      //当前帧图像
    cv::Mat bgMat;      //背景图像
    cv::Mat subMat;     //差分图像
    cv::Mat bny_subMat; //二值化后的差分图像
    int cnt=0;          //记录帧数
    while(1)
    {
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY); //转换成灰度图

        if (cnt == 0)
        {   //第一帧，获取背景图像
            frame.copyTo(bgMat);
        }
        else
        {   //第二帧开始和背景差分（背景图像和当前图像相减）
            absdiff(frame, bgMat, subMat);
            //差分结果二值化
            threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

            //imshow("frame", frame);
            //imshow("bgMat", bgMat);
            imshow("b_subMat", bny_subMat);
            imshow("subMat", subMat);
            waitKey(30);
        }

        cnt++;
    }

    return 0;
}
