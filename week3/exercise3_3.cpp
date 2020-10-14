/* ���ûص��������ж�ֵ�� */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

string window_name = "binaryMat";

void threshold_Mat(int th, void* data)
{
    Mat src = *(Mat*)(data);
    Mat dst;

    threshold(src, dst, th, 255, 0);    //��ֵ��

    imshow(window_name, dst);
}

int main()
{
    Mat srcMat;
    Mat gryMat;
    int lowTh = 30;
    int maxTh = 255;

    srcMat = imread(".//coin.png");
    if(!srcMat.data)    //�ж������Ƿ�����
    {
        cout << "ͼ������ʧ��" << endl;
        return 0;
    }
    imshow(window_name, srcMat);

    cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);  //ת���ɻҶ�ͼ
    imshow(window_name, gryMat);

    createTrackbar("threshold",
                   window_name,
                   &lowTh,
                   maxTh,
                   threshold_Mat,
                   &gryMat);                //���ûص�����

    waitKey(0);
    return 0;
}
