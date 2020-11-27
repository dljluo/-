/* ��ϰ9-1 �ֶ�ʵ��HOG���ӣ��Ƚ�����ͼƬ���ƶ� */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int calcHOG(cv::Mat frame, float *hist, int nAngle, int cellSize);
float normL2(float *histA, float *histB, int bins);

int main()
{
    cv::Mat refMat, plMat, bgMat;
    //��ȡͼ��
    refMat = imread("./hogTemplate.jpg", 0);
    plMat = imread("./pl.jpg", 0);
    bgMat = imread("./bg.jpg", 0);
    if(refMat.empty()) return -1;
    if(plMat.empty()) return -1;
    if(bgMat.empty()) return -1;
    imshow("refMat", refMat);
    imshow("plMat", plMat);
    imshow("bgMat", bgMat);

    //��ͼ���Ϊ���16*16��С��cell���Ƕ�����Ϊ8
    int cellSize = 16;
    int nAngle = 8;

    //����xy������cell����Ŀ
    int X = refMat.cols / cellSize;
    int Y = refMat.rows / cellSize;

    int bins = X * Y * nAngle;
    //��̬��������洢ֱ��ͼ����
    float * ref_hist = new float[bins];
    memset(ref_hist, 0, sizeof(float)*bins);
    float * pl_hist = new float[bins];
    memset(pl_hist, 0, sizeof(float)*bins);
    float * bg_hist = new float[bins];
    memset(bg_hist, 0, sizeof(float)*bins);

    int reCode = 0;
    //������������ͼƬ��HOG
    reCode = calcHOG(refMat, ref_hist, nAngle, cellSize);
    reCode = calcHOG(plMat, pl_hist, nAngle, cellSize);
    reCode = calcHOG(bgMat, bg_hist, nAngle, cellSize);

    if (reCode != 0)
        return -1;

    //����ֱ��ͼ����
    float dis1 = normL2(ref_hist, pl_hist, bins);
    float dis2 = normL2(ref_hist, bg_hist, bins);


    cout << "dis1: " << dis1 << endl;
    cout << "dis2: " << dis2 << endl;

    delete[] ref_hist;
    delete[] pl_hist;
    delete[] bg_hist;
    waitKey(0);
    return 0;
}

/** HOG���Ӻ��������ͼ��ֱ��ͼ **/
int calcHOG(cv::Mat frame, float *hist, int nAngle, int cellSize)
{
    //����xy������cell����Ŀ
    int nX = frame.cols / cellSize;
    int nY = frame.rows / cellSize;

    //�����ݶȺͽǶ�
    Mat gx, gy;
    Mat mag, angle;
    Sobel(frame, gx, CV_32F, 1, 0, 1);
    Sobel(frame, gy, CV_32F, 0, 1, 1);
    //x�����ݶȣ�y�����ݶȣ��ݶȣ��Ƕȣ����Ϊ����true/�Ƕ�false
    cartToPolar(gx, gy, mag, angle, true);



    for (int i=0; i<nY; i++)
    {
        for (int j=0; j<nX; j++)
        {
            cv::Mat roiMat;
            cv::Mat roiMag;
            cv::Mat roiAgl;

            Rect roi;
            roi.x = j*cellSize;
            roi.y = i*cellSize;
            roi.height = cellSize;
            roi.width = cellSize;
            //��ֵͼ��
            roiMat = frame(roi);
            roiMag = mag(roi);
            roiAgl = angle(roi);
            //��ǰcell��һ��Ԫ���������е�λ��
            int head = (i*nX + j)*nAngle;

            for (int n=0; n<roiMat.rows; n++)
            {
                uchar* magdata = roiMag.ptr<uchar>(n);
                uchar* agldata = roiAgl.ptr<uchar>(n);
                for (int m=0; m<roiMat.cols; m++)
                {
                    hist[head + (int)(agldata[m]/45)] += magdata[m];
                }
            }
        }
    }

    return 0;

}

/** ֱ��ͼ���ƶȼ��㺯��������ŷ����þ��� **/
float normL2(float *histA, float *histB, int bins)
{
    float dis = 0;

    for (int i=0; i<bins; i++)
    {
        dis += pow((histA[i] - histB[i]), 2);
    }

    dis = sqrt(dis);
    return dis;
}
