/* 计算并绘制直方图 */
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cv::Mat image = imread("D:\\Programming\\CC++\\DigitalImageCode\\1.jpg");   //读取图像
    cv::Mat dispMatGray(256,256,CV_8UC3,Scalar(255,255,255));    //建立直方图画布
    cv::Mat dispMatR(256,256,CV_8UC3,Scalar(255,255,255));
    cv::Mat dispMatG(256,256,CV_8UC3,Scalar(255,255,255));
    cv::Mat dispMatB(256,256,CV_8UC3,Scalar(255,255,255));

    float GrayHistgram[256]={0}, RHistgram[256]={0}, GHistgram[256]={0}, BHistgram[256]={0};    //定义存储数组并初始化
    int gray;                   //灰度
    int height = image.rows;    //行数
    int width = image.cols;     //列数

    //遍历图像像素点并统计
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            BHistgram[image.at<Vec3b>(j,i)[0]]++;
            GHistgram[image.at<Vec3b>(j,i)[1]]++;
            RHistgram[image.at<Vec3b>(j,i)[2]]++;
            gray = saturate_cast<uchar>(0.2989*image.at<Vec3b>(j,i)[2]+0.5870*image.at<Vec3b>(j,i)[1]+0.1140*image.at<Vec3b>(j,i)[0]);  //计算灰度
            GrayHistgram[gray]++;
        }
    }

    for(int k=0; k<256; k++)
    {   //归一化
        BHistgram[k] = BHistgram[k]/(height*width);
        GHistgram[k] = GHistgram[k]/(height*width);
        RHistgram[k] = RHistgram[k]/(height*width);
        GrayHistgram[k] = GrayHistgram[k]/(height*width);

        //绘制直线段
        line(dispMatGray,Point(k,256),Point(k,256-GrayHistgram[k]*10000),CV_RGB(0,0,0),1,8,0);
        line(dispMatR,Point(k,256),Point(k,256-RHistgram[k]*10000),CV_RGB(255,0,0),1,8,0);
        line(dispMatG,Point(k,256),Point(k,256-GHistgram[k]*10000),CV_RGB(0,255,0),1,8,0);
        line(dispMatB,Point(k,256),Point(k,256-BHistgram[k]*10000),CV_RGB(0,0,255),1,8,0);
    }

    //显示直方图图像
    imshow("dispMatGray", dispMatGray);
    imshow("dispMatR", dispMatR);
    imshow("dispMatG", dispMatG);
    imshow("dispMatB", dispMatB);
    waitKey(0);
    return 0;
}
