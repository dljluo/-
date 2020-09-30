/* 使用OpenCV进行简单绘图 */
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    cv::Mat dispMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\1.jpg");
    cv::Point circle_pt, line_pt1, line_pt2;
    cv::Rect rect;

    circle_pt.x = 100;      //圆心坐标
    circle_pt.y = 100;
    line_pt1.x = 50;        //线段起始点坐标
    line_pt1.y = 50;
    line_pt2.x = 150;
    line_pt2.y = 150;
    rect.x = 40;            //矩形端点坐标及长宽
    rect.y = 40;
    rect.width = 200;
    rect.height = 120;

    circle(dispMat,circle_pt,50,CV_RGB(255,0,0),1,8,0);     //(目标图像，圆心点，半径，颜色，线条粗细（-1为实心圆），领接关系默认8和0)
    line(dispMat,line_pt1,line_pt2,CV_RGB(0,255,0),5,8,0);  //(目标图像，起点，终点，颜色，线条粗细，领接关系默认8和0)
    rectangle(dispMat,rect,CV_RGB(0,0,255),3,8,0);          //(目标图像，被绘制矩形，颜色，线条粗细(-1为实心矩形)，领接关系默认8和0)

    imshow("dispMat",dispMat);
    waitKey(0);
    return 0;
}
