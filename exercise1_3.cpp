#include <iostream>
#include <opencv2\opencv.hpp>
using namespace cv;

int main()
{
    cv::Mat srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\2.jpg");
    int height = srcMat.rows;   //行数
    int width = srcMat.cols;    //每行元素的总元素数量
    uchar threshold = 100;
    for (int j=0; j<height; j++)
    {
        for (int i=0; i<width; i++)
        {
            //---------------开始处理每个像素---------------
            uchar average = (srcMat.at<Vec3b>(j,i)[0] + srcMat.at<Vec3b>(j,i)[1] + srcMat.at<Vec3b>(j,i)[2])/3;
            if (average > threshold)
                average = 255;
            else
                average = 0;
            srcMat.at<Vec3b>(j,i)[0] = average;
            srcMat.at<Vec3b>(j,i)[1] = average;
            srcMat.at<Vec3b>(j,i)[2] = average;
            //---------------结束像素处理-------------------
        }//单行处理结束
    }
    imshow("src",srcMat);
    waitKey(0);
    return 0;
}

