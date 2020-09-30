/* ���㲢����ֱ��ͼ */
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cv::Mat image = imread("D:\\Programming\\CC++\\DigitalImageCode\\1.jpg");   //��ȡͼ��
    cv::Mat dispMatGray(256,256,CV_8UC3,Scalar(255,255,255));    //����ֱ��ͼ����
    cv::Mat dispMatR(256,256,CV_8UC3,Scalar(255,255,255));
    cv::Mat dispMatG(256,256,CV_8UC3,Scalar(255,255,255));
    cv::Mat dispMatB(256,256,CV_8UC3,Scalar(255,255,255));

    float GrayHistgram[256]={0}, RHistgram[256]={0}, GHistgram[256]={0}, BHistgram[256]={0};    //����洢���鲢��ʼ��
    int gray;                   //�Ҷ�
    int height = image.rows;    //����
    int width = image.cols;     //����

    //����ͼ�����ص㲢ͳ��
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            BHistgram[image.at<Vec3b>(j,i)[0]]++;
            GHistgram[image.at<Vec3b>(j,i)[1]]++;
            RHistgram[image.at<Vec3b>(j,i)[2]]++;
            gray = saturate_cast<uchar>(0.2989*image.at<Vec3b>(j,i)[2]+0.5870*image.at<Vec3b>(j,i)[1]+0.1140*image.at<Vec3b>(j,i)[0]);  //����Ҷ�
            GrayHistgram[gray]++;
        }
    }

    for(int k=0; k<256; k++)
    {   //��һ��
        BHistgram[k] = BHistgram[k]/(height*width);
        GHistgram[k] = GHistgram[k]/(height*width);
        RHistgram[k] = RHistgram[k]/(height*width);
        GrayHistgram[k] = GrayHistgram[k]/(height*width);

        //����ֱ�߶�
        line(dispMatGray,Point(k,256),Point(k,256-GrayHistgram[k]*10000),CV_RGB(0,0,0),1,8,0);
        line(dispMatR,Point(k,256),Point(k,256-RHistgram[k]*10000),CV_RGB(255,0,0),1,8,0);
        line(dispMatG,Point(k,256),Point(k,256-GHistgram[k]*10000),CV_RGB(0,255,0),1,8,0);
        line(dispMatB,Point(k,256),Point(k,256-BHistgram[k]*10000),CV_RGB(0,0,255),1,8,0);
    }

    //��ʾֱ��ͼͼ��
    imshow("dispMatGray", dispMatGray);
    imshow("dispMatR", dispMatR);
    imshow("dispMatG", dispMatG);
    imshow("dispMatB", dispMatB);
    waitKey(0);
    return 0;
}
