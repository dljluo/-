/* ��ϰ4-4 ����ͼ���ڻ�������Ŀ */
#include <iostream>
#include <opencv2/opencv.hpp>
#define kernelSize 5        //����ṹԪ�ش�С
#define clipSize 400        //�����������ͨ������ı��γ�����ֵ����������ǰ���ͱ���

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
    int backgroundNum=0;  //��������

    srcMat = imread(".\\clip.jpg",0);   //��ȡͼ��ת���ɻҶ�ͼ
    dstMat = 255 - srcMat;              //ɫ����ת
    threshold(dstMat, resultMat, 100, 255, THRESH_BINARY);  //��򷨶�ֵ��
    kernel = getStructuringElement(MORPH_RECT, Size(kernelSize,kernelSize));  //����ṹԪ��
    morphologyEx(resultMat, openMat, 2, kernel);  //������

    ConnectedNum = connectedComponentsWithStats(openMat,
                                                labels,
                                                stats,
                                                centroids); //��ͨ����

    for(int i=0; i<ConnectedNum; i++)       //����ǰ���ͱ�����ͨ��
    {
        if(stats.at<int>(i,CC_STAT_WIDTH)>clipSize || stats.at<int>(i,CC_STAT_HEIGHT)>clipSize)
            backgroundNum++;
    }

    cout << ConnectedNum-backgroundNum << endl;
    //cout << stats << endl;    //����Ԥ��clipSizeֵ
    imshow("resultMat", resultMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}
