/** ��ϰ13-1 ģ��ƥ�书�ܵ�����ϰ **/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int calcHOG(cv::Mat frame, float *hist, int nAngle, int cellSize);
float normL2(float *histA, float *histB, int bins);


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
    cv::Mat tempMat;    //����Ĵ�ͼ��
    cv::Mat refMat;     //ģ��ͼ��
    cv::Mat resultMat;  //ģ��ƥ��������
    cv::Mat dispMat;    //�����ʾͼ��

    int cnt = 0;            //��ʼ֡
    int match_method = 0;   //���ƶ��㷨

    while (1)
    {
        cap >> frame;

        if (cnt == 0)
        {
            Rect2d r;
            r = selectROI(frame, true);
            tempMat = frame(r);
            tempMat.copyTo(refMat);
            destroyAllWindows();            //�������д���
            cnt++;
        }
        //imshow("ref",refMat);

        //ģ��ƥ�亯��
        //TM_SQDIFF=0;TM_SQDIFF_NORMED=1;
        //TM_CCORR=2;TM_CCORR_NORMED=3;TM_CCOEFF=4;TM_CCOEFF_NORMED=5
        matchTemplate(frame, refMat, resultMat, match_method);

        //��һ��
        normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

        double minVal, maxVal;
        Point minLoc, maxLoc;
        Point matchLoc;
        //Ѱ�Ҽ�ֵ
        minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        //ƥ�䷽ʽ��TM_SQDIFF��TM_SQDIFF_NRMED��ƥ����ֵԽ��ƥ��Ч��Խ��
        //����������ƥ����ֵԽ��ƥ��Ч��Խ��
        matchLoc = minLoc;

        //����ƥ����ͼ�����
        frame.copyTo(dispMat);
        rectangle(dispMat, matchLoc, Point(matchLoc.x+refMat.cols, matchLoc.y+refMat.rows), Scalar(0,255,0), 2, 8, 0);

        imshow("dispMat", dispMat);
        waitKey(30);
    }

    return 0;
}
