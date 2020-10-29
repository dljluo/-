/* ��ϰ5-5 ĥƤ����ʹ����Ƥ�����ֱ�⻬ */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap;

    cap.open(0);
    if(!cap.isOpened()) //����Ƿ��ܴ򿪱�������ͷ
    {
        std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
        return -1;
    }

    //0-180
    //��ɫ
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
        Mat srcMat, dstMat;     //ԭͼ�����ͼ��
        Mat hsvMat;             //ԭͼ��hsv��ʽ
        Mat mask;               //��Ĥ
        Mat skinMat, otherMat;  //Ƥ������ͼ�񡢷�Ƥ������ͼ��
        Mat buffingMat;         //ĥƤ������Ƥ��ͼ��

        cap >> srcMat;          //�洢����ͷ��ȡ����֡ͼ��
        cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);    //��ԭͼת��hsv��ʽ
        cv::inRange(hsvMat, Scalar(i_minH,i_minS,i_minV), Scalar(i_maxH,i_maxS,i_maxV), mask); //������ֵ��Χ��ֵ��

        srcMat.copyTo(skinMat, mask);               //��Ĥ����Ƥ������ͼ��skinMat
        srcMat.copyTo(otherMat, (255-mask));        //����Ƥ������ͼ���Ƶ�otherMat
        GaussianBlur(skinMat, buffingMat, Size(5,5), 3, 3, BORDER_DEFAULT);      //��˹ƽ���˲�,��Ƥ��ͼ��ģ������
        dstMat = buffingMat + otherMat;             //�ϳ�ĥƤ������ͼ��

        imshow("ԭͼ��", srcMat);
        imshow("ĥƤ��ͼ��", dstMat);

        waitKey(10);
    }

    return 0;
}
