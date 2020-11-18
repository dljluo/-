/* ��ϰ8-3 ͨ��ͼ����̬�����ҳ��豭 */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    Mat dstMat;
    srcMat = imread("./cup.jpg");    //��ȡͼ��
    if(srcMat.empty()) return -1;
    resize(srcMat, dstMat, Size(srcMat.cols*0.1,srcMat.rows*0.1));  //��ԭͼ������С
    imshow("src", dstMat);

    //��ɫhsv��Χ
    double i_minHA = 0;
    double i_maxHA = 10;
    double i_minHB = 156;
    double i_maxHB = 180;
    double i_minS = 70;
    double i_maxS = 255;
    double i_minV = 46;
    double i_maxV = 255;

    Mat hsvMat;
    Mat bnyAPart, bnyBPart;
    Mat bnyMat;
    cvtColor(dstMat, hsvMat, COLOR_BGR2HSV);    //��ԭͼת��hsv��ʽ
    //������ɫ��������ǰ������
    inRange(hsvMat, Scalar(i_minHA,i_minS,i_minV), Scalar(i_maxHA,i_maxS,i_maxV), bnyAPart);
    inRange(hsvMat, Scalar(i_minHB,i_minS,i_minV), Scalar(i_maxHB,i_maxS,i_maxV), bnyBPart);
    bnyMat = bnyAPart + bnyBPart;
    //imshow("A", bnyAPart);
    //imshow("B", bnyBPart);

    Mat kernel;     //�ṹԪ��
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //����ṹԪ��
    morphologyEx(bnyMat, openMat, 2, kernel);               //������
    imshow("openMat", openMat);

    vector<vector<Point>> contours; //��������
    vector<Vec4i> hierarchy;        //�����̳й�ϵ
    //Ѱ����ͨ��
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        RotatedRect rbox = minAreaRect(contours[i]);    //��С����ı���
        double factor;  //Բ�ζ�
        //����Բ�ζ�   S=(C^2)/4��
        factor = (contourArea(contours[i]) * 4 * CV_PI) / (pow(arcLength(contours[i], true), 2));
        cout << "factor:" << factor << endl;

        //���Ʋ豭����ı���
        if(factor > 0.8)
        {
            Point2f vtx[4];      //��������ı����ĸ�����
            rbox.points(vtx);    //����4�������ֵ
            for(unsigned int j=0; j<4; j++)
                line(dstMat, vtx[j], vtx[(j+1)%4], Scalar(200,0,240), 1, CV_AA);
        }
    }

    imshow("dst", dstMat);
    waitKey(0);
    return 0;
}
