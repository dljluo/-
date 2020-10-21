/* ��ϰ4-3 ʹ�ô�򷨷ָ�ͼ����ͨ���Ǻ����ԭ����� */
#include <iostream>
#include <opencv2/opencv.hpp>
#define kernelSize 25       //����ṹԪ�ش�С
using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;         //ԭͼ
    Mat dstMat;         //ԭͼɫ����ת���ͼ��
    Mat resultMat;      //��ֵ�����ͼ��
    Mat openMat;        //��������ͼ��
    Mat kernel;         //�ṹԪ��
    Mat labels, stats, centroids;   //��ͨ���ǩ�š�״̬�������ľ���
    int ConnectedNum;   //��ͨ������

    srcMat = imread(".//PCB.jpg",0);    //��ȡͼ��ת���ɻҶ�ͼ
    dstMat = 255 - srcMat;              //ɫ����ת
    threshold(dstMat, resultMat, 100, 255, THRESH_BINARY);  //��򷨶�ֵ��
    kernel = getStructuringElement(MORPH_RECT, Size(kernelSize,kernelSize));  //����ṹԪ��
    morphologyEx(resultMat, openMat, 2, kernel);  //������

    ConnectedNum = connectedComponentsWithStats(openMat,
                                                labels,
                                                stats,
                                                centroids); //��ͨ����

    cout << ConnectedNum-1 << endl;
    //cout << stats << endl;    //�����ж�kernelSize��Χ
    imshow("result", resultMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}
