/* 练习5-5 磨皮程序：使人物皮肤部分变光滑 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap;

    cap.open(0);
    if(!cap.isOpened()) //检查是否能打开本地摄像头
    {
        std::cout << "不能打开视频文件" << std::endl;
        return -1;
    }

    //0-180
    //肤色
    double i_minH = 0;
    double i_maxH = 20;
    //0-255
    double i_minS = 36;
    double i_maxS = 255;
    //0-255
    double i_minV = 55;
    double i_maxV = 255;

    while(1)
    {
        Mat srcMat, dstMat;     //原图像，输出图像
        Mat hsvMat;             //原图像hsv格式
        Mat mask;               //掩膜
        Mat skinMat, otherMat;  //皮肤部分图像、非皮肤部分图像
        Mat buffingMat;         //磨皮处理后的皮肤图像

        cap >> srcMat;          //存储摄像头读取到的帧图像
        cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);    //将原图转成hsv格式
        cv::inRange(hsvMat, Scalar(i_minH,i_minS,i_minV), Scalar(i_maxH,i_maxS,i_maxV), mask); //根据阈值范围二值化

        srcMat.copyTo(skinMat, mask);               //掩膜复制皮肤部分图像到skinMat
        srcMat.copyTo(otherMat, (255-mask));        //将非皮肤部分图像复制到otherMat
        GaussianBlur(skinMat, buffingMat, Size(5,5), 3, 3, BORDER_DEFAULT);      //高斯平滑滤波,对皮肤图像模糊处理
        dstMat = buffingMat + otherMat;             //合成磨皮后的输出图像

        imshow("原图像", srcMat);
        imshow("磨皮后图像", dstMat);

        waitKey(10);
    }

    return 0;
}
