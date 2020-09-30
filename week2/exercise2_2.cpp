/* ��ϰ2.���ñ�������ͷ */
#include <iostream>
#include <opencv2\opencv.hpp>

#define CAP_PROR_FPS 5  //��Ƶ�ļ�֡���ʼ�֡��

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap;

    cap.open(0);        //�򿪱�����һ������ͷ
    //cap.open("D:\\Programming\\CC++\\DigitalImageCode\\1.mp4"); //�򿪱�����Ƶ�ļ�

    if(!cap.isOpened()) //����Ƿ��ܴ򿪱�������ͷ
    {
        std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
        return -1;
    }

    double fps = cap.get(CAP_PROR_FPS);     //get(5)Ϊ֡���ʣ�get(7)Ϊ��֡��
    std::cout << "fps" << fps << std::endl;
    while(1)
    {
        cv::Mat frame;
        bool rSucess = cap.read(frame);
        if(!rSucess)
        {
            std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
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
