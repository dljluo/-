/* ��ϰ7-1 ���Զ��ü���ͼ����ת */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cv::Mat srcMat;             //ԭͼ��
    cv::Mat dstMatA,dstMatB;    //���ͼ��
    //��ȡԭͼ��
    srcMat = cv::imread("D:\\Programming\\CC++\\DigitalImageCode\\orilena.png", 1);
    if(srcMat.empty()) return -1;

    float angle = -10.0;//��ת�Ƕ�-40��
    float scale = 1;    //���ű���
    //��ȡ��ת����
    cv::Point2f center(srcMat.cols/2.0, srcMat.rows/2.0);
    //��ȡ����ı���
    cv::Rect bbox = cv::RotatedRect(center, srcMat.size(), angle).boundingRect();

    /* A��任����ת�󲻸ı�ԭͼ�ߴ磬�����ͼ���� */
    //��ȡ�任����
    cv::Mat rotA = cv::getRotationMatrix2D(center, angle, scale);
    //�����������������ı��������꣩
    rotA.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rotA.at<double>(1, 2) += bbox.height / 2.0 - center.y;
    //����任
    cv::warpAffine(srcMat, dstMatA, rotA, bbox.size());

    /* B��任:��ת��ı�ԭͼ�ߴ磬�����ͼ��ߴ���ԭͼһ��*/
    scale = srcMat.cols * 1.0 / bbox.width;
    cv::Mat rotB = cv::getRotationMatrix2D(center, angle, scale);
    cv::warpAffine(srcMat, dstMatB, rotB, srcMat.size());

    //��ʾԭͼ������ͼ��
    imshow("src", srcMat);
    imshow("��ת�󲻸ı�ԭͼ�ߴ磬�����ͼ����", dstMatA);
    imshow("��ת��ı�ԭͼ�ߴ磬�����ͼ��ߴ���ԭͼһ��", dstMatB);
    waitKey(0);

    return 0;
}
