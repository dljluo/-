/**练习11-2 实现高斯建模及背景差分**/
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())     //检查是否能打开摄像头
    {
        std::cout << "不能打开摄像头" << std::endl;
        return -1;
    }

    cv::Mat frame;      //当前帧图像
    cv::Mat subMat;     //差分图像
    cv::Mat bny_subMat; //二值化后的差分图像
    cv::Mat LMat;       //均值图像
    cv::Mat sigema;     //σ
    int cnt = 0;        //帧数序号
    int N = 10;         //预读取的前N张图像
    int Th = 3;
    cv::Mat bgMat[N];   //前N帧图像数据

    while(1)
    {
        cap >> frame;
        cvtColor(frame, frame, COLOR_BGR2GRAY); //转换成灰度图

        if (cnt == 0)
        {
            //初始化
            frame.copyTo(bgMat[cnt]);
            frame.copyTo(LMat);
            LMat = LMat / N;
            sigema = cv::Mat::zeros(frame.cols, frame.rows, CV_32F);
        }
        else if (cnt < N)
        {
            //存储前N帧背景图像并计算均值图像数据
            frame.copyTo(bgMat[cnt]);
            LMat += bgMat[cnt] / N;
        }
        else
        {
            //计算方差
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
            //当前帧图像和均值图像相减得差分图像
            absdiff(frame, LMat, subMat);
            //对差分图像进行高斯建模判断
            for (int y=0; y<LMat.rows; y++)
            {
                uchar* sub = subMat.ptr<uchar>(y);
                uchar* si = sigema.ptr<uchar>(y);
                for (int x=0; x<LMat.cols; x++)
                {
                    //计算标准差σ
                    si[x] = sqrt(si[x]);
                    //判断差值是否在背景变化范围之外
                    if (sub[x] < Th*si[x])
                        sub[x] = 0;
                }
            }
            //差分结果二值化
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
