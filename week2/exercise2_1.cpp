/* 练习1.分离RGB三通道 */
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    cv::Mat src_color = imread("D:\\Programming\\CC++\\DigitalImageCode\\1.jpg");
    std::vector<cv::Mat> channels;
    cv::split(src_color, channels); //调用函数分离图像RGB三通道
    cv::Mat B = channels.at(0);
    cv::Mat G = channels.at(1);
    cv::Mat R = channels.at(2);
    cv::imshow("red", R);
    cv::imshow("green", G);
    cv::imshow("blue", B);
    cv::imshow("original Mat", src_color);
    waitKey(0);
    return 0;
}
