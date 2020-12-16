/**��ϰ11-2 ʵ�ָ�˹��ģ���������**/
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
    cv::Mat subMat;     //���ͼ��
    cv::Mat bny_subMat; //��ֵ����Ĳ��ͼ��
    cv::Mat LMat;       //��ֵͼ��
    cv::Mat sigema;     //��
    int cnt = 0;        //֡�����
    int N = 10;         //Ԥ��ȡ��ǰN��ͼ��
    int Th = 3;
    cv::Mat bgMat[N];   //ǰN֡ͼ������

    while(1)
    {
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY); //ת���ɻҶ�ͼ

        if (cnt == 0)
        {
            //��ʼ��
            frame.copyTo(bgMat[cnt]);
            frame.copyTo(LMat);
            LMat = LMat / N;
            sigema = cv::Mat::zeros(frame.cols, frame.rows, CV_32F);
        }
        else if (cnt < N)
        {
            //�洢ǰN֡����ͼ�񲢼����ֵͼ������
            frame.copyTo(bgMat[cnt]);
            LMat += bgMat[cnt] / N;
        }
        else
        {
            //���㷽��
            for (int n=0; n<N; n++)
            {
                for (int y=0; y<LMat.rows; y++)
                {
                    uchar* bg = bgMat[n].ptr<uchar>(y);
                    uchar* L = LMat.ptr<uchar>(y);
                    uchar* si = sigema.ptr<uchar>(y);
                    for (int x=0; x<LMat.cols; x++)
                    {
                        si[x] += pow((bg[x]-L[x]), 2) / N;
                    }
                }
            }
            //��ǰ֡ͼ��;�ֵͼ������ò��ͼ��
            absdiff(frame, LMat, subMat);
            //�Բ��ͼ����и�˹��ģ�ж�
            for (int y=0; y<LMat.rows; y++)
            {
                uchar* sub = subMat.ptr<uchar>(y);
                uchar* si = sigema.ptr<uchar>(y);
                for (int x=0; x<LMat.cols; x++)
                {
                    //�����׼���
                    si[x] = sqrt(si[x]);
                    //�жϲ�ֵ�Ƿ��ڱ����仯��Χ֮��
                    if (sub[x] < Th*si[x])
                        sub[x] = 0;
                }
            }
            //��ֽ����ֵ��
            threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

            imshow("LMat", LMat);
            imshow("subMat", subMat);
            imshow("b_subMat", bny_subMat);
            waitKey(30);
        }

        cnt++;
    }

    return 0;
}
