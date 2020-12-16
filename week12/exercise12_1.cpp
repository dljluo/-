/**��ϰ11-1 ʵ�ֱ������**/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())     //����Ƿ��ܴ�����ͷ
    {
        std::cout << "���ܴ�����ͷ" << std::endl;
        return -1;
    }

    cv::Mat frame;      //��ǰ֡ͼ��
    cv::Mat bgMat;      //����ͼ��
    cv::Mat subMat;     //���ͼ��
    cv::Mat bny_subMat; //��ֵ����Ĳ��ͼ��
    int cnt=0;          //��¼֡��
    while(1)
    {
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY); //ת���ɻҶ�ͼ

        if (cnt == 0)
        {   //��һ֡����ȡ����ͼ��
            frame.copyTo(bgMat);
        }
        else
        {   //�ڶ�֡��ʼ�ͱ�����֣�����ͼ��͵�ǰͼ�������
            absdiff(frame, bgMat, subMat);
            //��ֽ����ֵ��
            threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

            //imshow("frame", frame);
            //imshow("bgMat", bgMat);
            imshow("b_subMat", bny_subMat);
            imshow("subMat", subMat);
            waitKey(30);
        }

        cnt++;
    }

    return 0;
}
