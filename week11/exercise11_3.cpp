/** ��ϰ11-3 ͨ��gamma�������ͼ���عⲻ�� **/
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
    imshow("�ý���", srcMat);

    int Gam_value = 50;
    int maxGam = 1000;
    createTrackbar("��*100",
                   "�ý���",
                   &Gam_value,
                   maxGam,
                   GammaDemo,
                   &srcMat);
    waitKey(0);
    return 0;
}

void GammaDemo(int Gam, void* usrdata)
{
    cv::Mat srcMat = *(Mat*)(usrdata);      //ǿ������ת��
    cv::Mat dstMat;
    srcMat.copyTo(dstMat);
    int num_channels = srcMat.channels();   //����ͼ��ͨ����
//    cout << "channels: " << num_channels << endl;
    float gamma = Gam*1.0 / 100;            //����gammaֵ

    if (num_channels == 1)      //�Ե�ͨ��ͼ����
    {
        equalizeHist(srcMat, srcMat);
        GammaChange(srcMat, dstMat, gamma);
    }
    else                        //�Զ�ͨ��ͼ����
    {
        std::vector<cv::Mat> channels_src;
        std::vector<cv::Mat> channels_dst(num_channels);
        //����ͼ��RGB��ͨ��
        split(srcMat, channels_src);
        //������ͨ���ֱ����ͼ����ǿ����
        for (int idx=0; idx<num_channels; idx++)
        {
            equalizeHist(channels_src[idx], channels_src[idx]);         //ֱ��ͼ����
            GammaChange(channels_src[idx], channels_dst[idx], gamma);   //�ý���
        }
        //�ϲ�������RGB��ͨ��
        merge(channels_dst, dstMat);
    }

    imwrite("dstMat.png", dstMat);
    imshow("�ý���", dstMat);
}

/****************��ͨ��ͼ���Gamma��������******************/
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
     //������������
    for (int j=0; j<height; j++)
    {
        for (int i=0; i<width; i++)
        {
            grayIn = src.ptr<uchar>(j)[i]*1.0 / 255; //��һ���Ҷ�ֵ
            grayOut = pow(grayIn, gamma);            //gamma�任
            dst.ptr<uchar>(j)[i] = grayOut*255;      //��ֵ�����ͼ����
        }
    }
    return 0;
}
