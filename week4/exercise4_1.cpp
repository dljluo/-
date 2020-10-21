/* ��ϰ4-1 ��ͼ����ж�ֵ����ֱ�������͡���ʴ��������ͱ����� */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;     //ԭͼ
    Mat resultMat;  //��ֵ�����ͼ��
    Mat erodeMat, dilateMat, openMat, closeMat; //��̬ѧ������ͼ��
    Mat kernel;     //�ṹԪ��

    srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\coin.jpg",0); //��ȡ��ת���ɻҶ�ͼ
    threshold(srcMat, resultMat, 100, 255, THRESH_BINARY);  //��ֵ��

    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //����ṹԪ��
    morphologyEx(resultMat, erodeMat,  0, kernel);  //��ʴ����
    morphologyEx(resultMat, dilateMat, 1, kernel);  //��������
    morphologyEx(resultMat, openMat,   2, kernel);  //������
    morphologyEx(resultMat, closeMat,  3, kernel);  //������


    imshow("ԭͼ�ĻҶ�ͼ", srcMat);
    imshow("��ֵ��ͼ��",   resultMat);
    imshow("��ʴ����ͼ��", erodeMat);
    imshow("��������ͼ��", dilateMat);
    imshow("������ͼ��",   openMat);
    imshow("������ͼ��",   closeMat);

    waitKey(0);
    return 0;
}
