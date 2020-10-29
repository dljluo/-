/* ��ϰ5-2 ��ֵ�˲� */
#include <iostream>
#include <opencv2/opencv.hpp>
#define ksize 11         //����ߴ�
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;

    cap.open(0);

    if(!cap.isOpened()) //����Ƿ��ܴ򿪱�������ͷ
    {
        std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
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
            std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
            break;
        }
        else
        {
            blur(srcMat, dstMat, Size(ksize,ksize), Point(-1,-1), BORDER_DEFAULT);      //��ֵ�˲�
            cv::imshow("srcMat", srcMat);
            cv::imshow("dstMat", dstMat);
        }
        waitKey(30);
    }

    return 0;
}
