/* ʹ��OpenCV���м򵥻�ͼ */
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    cv::Mat dispMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\1.jpg");
    cv::Point circle_pt, line_pt1, line_pt2;
    cv::Rect rect;

    circle_pt.x = 100;      //Բ������
    circle_pt.y = 100;
    line_pt1.x = 50;        //�߶���ʼ������
    line_pt1.y = 50;
    line_pt2.x = 150;
    line_pt2.y = 150;
    rect.x = 40;            //���ζ˵����꼰����
    rect.y = 40;
    rect.width = 200;
    rect.height = 120;

    circle(dispMat,circle_pt,50,CV_RGB(255,0,0),1,8,0);     //(Ŀ��ͼ��Բ�ĵ㣬�뾶����ɫ��������ϸ��-1Ϊʵ��Բ������ӹ�ϵĬ��8��0)
    line(dispMat,line_pt1,line_pt2,CV_RGB(0,255,0),5,8,0);  //(Ŀ��ͼ����㣬�յ㣬��ɫ��������ϸ����ӹ�ϵĬ��8��0)
    rectangle(dispMat,rect,CV_RGB(0,0,255),3,8,0);          //(Ŀ��ͼ�񣬱����ƾ��Σ���ɫ��������ϸ(-1Ϊʵ�ľ���)����ӹ�ϵĬ��8��0)

    imshow("dispMat",dispMat);
    waitKey(0);
    return 0;
}
