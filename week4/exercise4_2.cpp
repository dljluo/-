/* ��ϰ4-2 ��ͼ����ж�ֵ������ͨ���ǡ�������ͨ������ı��Ρ������������ */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;         //ԭͼ
    Mat resultMat;      //��ֵ�����ͼ��
    Mat boundingboxMat; //���Ƴ�ÿ����ͨ�������ı���ͼ��
    Mat labels, stats, centroids;   //��ͨ���ǩ�š�״̬�������ľ���
    int ConnectedNum;   //��ͨ������
    cv::Rect rect;

    srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\coin.jpg",0); //��ȡ��ת���ɻҶ�ͼ
    srcMat.copyTo(boundingboxMat);
    threshold(srcMat, resultMat, 100, 255, THRESH_BINARY);  //��ֵ��
    ConnectedNum = connectedComponentsWithStats(resultMat,
                                                labels,
                                                stats,
                                                centroids); //��ͨ����

    for(int i=1; i<ConnectedNum; i++)           //���Ƹ���ͨ�������ı���
    {
        rect.x = stats.at<int>(i,CC_STAT_LEFT);
        rect.y = stats.at<int>(i,CC_STAT_TOP);
        rect.width = stats.at<int>(i,CC_STAT_WIDTH);
        rect.height = stats.at<int>(i,CC_STAT_HEIGHT);
        rectangle(boundingboxMat, rect, CV_RGB(0,0,255),3,8,0);
    }

    cout << ConnectedNum-1 << endl;             //��������������ͨ�����
    //cout << stats << endl;
    imshow("boundingboxMat", boundingboxMat);
    waitKey(0);
    return 0;
}
