/** 练习11-2 直方图均衡 **/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    cv::Mat srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\exercise11_3\\Reimu11.png");
    if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
    imshow("srcMat", srcMat);

    cv::Mat dstMat;
    std::vector<cv::Mat> channels_src;
    std::vector<cv::Mat> channels_dst(3);
    split(srcMat, channels_src);        //分离图像RGB三通道
    //将三个通道分别进行直方图均衡
    equalizeHist(channels_src[0], channels_dst[0]);
    equalizeHist(channels_src[1], channels_dst[1]);
    equalizeHist(channels_src[2], channels_dst[2]);
    merge(channels_dst, dstMat);        //合并处理后的RGB三通道

    //imshow("B", channels_src[0]);
    //imshow("dstB", channels_dst[0]);
    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}
