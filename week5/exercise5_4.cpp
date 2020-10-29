/* ��ϰ5-4��Ե��ȡ */
#include <iostream>
#include <opencv2/opencv.hpp>
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
        cv::Mat dstMatX, dstMatY;
        bool rSucess = cap.read(srcMat);
        srcMat.copyTo(dstMatX);
        srcMat.copyTo(dstMatY);
        if(!rSucess)
        {
            std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
            break;
        }
        else
        {
            Sobel(srcMat, dstMatX, CV_8UC1, 1, 0, 3);       //��ȡˮƽ�����ϵı�Ե
            Sobel(srcMat, dstMatY, CV_8UC1, 0, 1, 3);       //��ȡ��ֱ�����ϵı�Ե
            cv::imshow("srcMat", srcMat);
            cv::imshow("X�����Ե", dstMatX);
            cv::imshow("Y�����Ե", dstMatY);
        }
        waitKey(30);
    }

    return 0;
}
