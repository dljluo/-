/* ��ϰ8-1 ͨ��ͼ����̬�����ҳ���̥�ϵ�Բ�� */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    srcMat = imread("./luntai.png");    //��ȡͼ��
    if(srcMat.empty()) return -1;
    imshow("src", srcMat);

    Mat fitMat;
    medianBlur(srcMat, fitMat, 7);      //��ֵ�˲�
    //imshow("fitMat", fitMat);

    Mat gryMat;
    cvtColor(fitMat, gryMat, COLOR_RGB2GRAY);   //RGBת�Ҷ�ͼ
    //imshow("gryMat", gryMat);

    Mat bnyMat;
    threshold((255-gryMat), bnyMat, 120, 255, THRESH_BINARY);   //��ֵ��
    //imshow("binary", bnyMat);

    Mat kernel;     //�ṹԪ��
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(7,7));  //����ṹԪ��
    morphologyEx(bnyMat, openMat, 2, kernel);               //������
    //imshow("openMat", openMat);

    vector<vector<Point>> contours; //��������
    vector<Vec4i> hierarchy;        //�����̳й�ϵ
    //Ѱ����ͨ��
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        double factor;  //Բ�ζ�
        //����Բ�ζ�   S=(C^2)/4��
        factor = (contourArea(contours[i]) * 4 * CV_PI) / (pow(arcLength(contours[i], true), 2));
        cout << "factor:" << factor << endl;

        if(factor > 0.8)
        {
            //����Բ��
            drawContours(srcMat, contours, i, Scalar(0,255,0), -1, 8);
        }
    }

    imshow("dst", srcMat);
    waitKey(0);
    return 0;
}
