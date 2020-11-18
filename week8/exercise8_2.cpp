/* ��ϰ8-2 ͨ��ͼ����̬�����ҳ�оƬ */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    srcMat = imread("./xinpian.jpg");    //��ȡͼ��
    if(srcMat.empty()) return -1;
    //imshow("src", srcMat);

    Mat gryMat;
    cvtColor(srcMat, gryMat, COLOR_RGB2GRAY);   //RGBת�Ҷ�ͼ
    //imshow("gryMat", gryMat);

    Mat bnyMat;
    threshold(gryMat, bnyMat, 150, 255, THRESH_BINARY);   //��ֵ��
    //imshow("binary", bnyMat);

    Mat kernel;     //�ṹԪ��
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //����ṹԪ��
    morphologyEx(bnyMat, openMat, 2, kernel);               //������
    //imshow("openMat", openMat);

    vector<vector<Point>> contours; //��������
    vector<Vec4i> hierarchy;        //�����̳й�ϵ
    //Ѱ����ͨ��
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        double hwr;  //�����
        RotatedRect rbox = minAreaRect(contours[i]);    //��С����ı���
        //���㳤���
        hwr = rbox.size.height / rbox.size.width;
        cout << "�����:" << hwr << endl;
        double S;   //���
        S = rbox.size.height * rbox.size.width;
        cout << "���" << S << endl;

        //����оƬ����
        if(hwr > 0.9 &&  hwr < 1.1 && S > 1000)
        {
            //����ı�������
            Point2f vtx[4];      //��������ı����ĸ�����
            rbox.points(vtx);    //����4�������ֵ
            for(unsigned int j=0; j<4; j++)
                line(srcMat, vtx[j], vtx[(j+1)%4], Scalar(255,0,0), 2, CV_AA);
            //оƬ����
            drawContours(srcMat, contours, i, Scalar(0,255,0), 1, 8);
        }
    }

    imshow("dst", srcMat);
    waitKey(0);
    return 0;
}
