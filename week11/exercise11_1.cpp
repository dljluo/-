/** ��ϰ11-1 ʵ��gamma���� **/
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
    float gamma = 0.4; //����gammaֵ
    float grayIn, grayOut;

    //������������
    int height = srcMat.rows;
    int width = srcMat.cols;
    for (int j=0; j<height; j++)
    {
        for (int i=0; i<width; i++)
        {
            grayIn = srcMat.ptr<uchar>(j)[i]*1.0 / 255; //��һ���Ҷ�ֵ
            grayOut = pow(grayIn, gamma);               //gamma�任
            dstMat.ptr<uchar>(j)[i] = grayOut*255;      //��ֵ�����ͼ����
        }
    }

    imshow("dstMat", dstMat);
    waitKey(0);
    return 0;
}
