/** 练习11-1 实现gamma矫正 **/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    cv::Mat srcMat = imread("./face.jpg", 0);
    if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
    imshow("srcMat", srcMat);

    cv::Mat dstMat;
    srcMat.copyTo(dstMat);
    float gamma = 0.4; //定义gamma值
    float grayIn, grayOut;

    //遍历所有像素
    int height = srcMat.rows;
    int width = srcMat.cols;
    for (int j=0; j<height; j++)
    {
        for (int i=0; i<width; i++)
        {
            grayIn = srcMat.ptr<uchar>(j)[i]*1.0 / 255; //归一化灰度值
            grayOut = pow(grayIn, gamma);               //gamma变换
            dstMat.ptr<uchar>(j)[i] = grayOut*255;      //赋值到输出图像上
        }
    }

    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}
