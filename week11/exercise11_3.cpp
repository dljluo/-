/** 练习11-3 通过gamma矫正解决图像曝光不足 **/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void GammaDemo(int Gam, void* usrdata);
int GammaChange(cv::Mat src, cv::Mat &dst, float gamma);

int main()
{
    cv::Mat srcMat = imread("./image.jpg");
    if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
    imshow("γ矫正", srcMat);

    int Gam_value = 50;
    int maxGam = 1000;
    createTrackbar("γ*100",
                   "γ矫正",
                   &Gam_value,
                   maxGam,
                   GammaDemo,
                   &srcMat);
    waitKey(0);
    return 0;
}

void GammaDemo(int Gam, void* usrdata)
{
    cv::Mat srcMat = *(Mat*)(usrdata);      //强制类型转换
    cv::Mat dstMat;
    srcMat.copyTo(dstMat);
    int num_channels = srcMat.channels();   //定义图像通道数
//    cout << "channels: " << num_channels << endl;
    float gamma = Gam*1.0 / 100;            //定义gamma值

    if (num_channels == 1)      //对单通道图像处理
    {
        equalizeHist(srcMat, srcMat);
        GammaChange(srcMat, dstMat, gamma);
    }
    else                        //对多通道图像处理
    {
        std::vector<cv::Mat> channels_src;
        std::vector<cv::Mat> channels_dst(num_channels);
        //分离图像RGB三通道
        split(srcMat, channels_src);
        //对三个通道分别进行图像增强处理
        for (int idx=0; idx<num_channels; idx++)
        {
            equalizeHist(channels_src[idx], channels_src[idx]);         //直方图均衡
            GammaChange(channels_src[idx], channels_dst[idx], gamma);   //γ矫正
        }
        //合并处理后的RGB三通道
        merge(channels_dst, dstMat);
    }

    imwrite("dstMat.png", dstMat);
    imshow("γ矫正", dstMat);
}

/****************单通道图像的Gamma矫正函数******************/
int GammaChange(cv::Mat src, cv::Mat &dst, float gamma)
{
    if (src.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
    src.copyTo(dst);

    float grayIn, grayOut;
    int height = src.rows;
    int width = src.cols;
     //遍历所有像素
    for (int j=0; j<height; j++)
    {
        for (int i=0; i<width; i++)
        {
            grayIn = src.ptr<uchar>(j)[i]*1.0 / 255; //归一化灰度值
            grayOut = pow(grayIn, gamma);            //gamma变换
            dst.ptr<uchar>(j)[i] = grayOut*255;      //赋值到输出图像上
        }
    }
    return 0;
}
