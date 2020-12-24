/** 练习13-1 模板匹配功能调用练习 **/
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
    if(!cap.isOpened())     //检查是否能打开摄像头
    {
        std::cout << "不能打开摄像头" << std::endl;
        return -1;
    }

    cv::Mat frame;      //当前帧图像
    cv::Mat tempMat;    //缓冲寄存图像
    cv::Mat refMat;     //模板图像
    cv::Mat resultMat;  //模板匹配结果矩阵
    cv::Mat dispMat;    //输出显示图像

    int cnt = 0;            //起始帧
    int match_method = 0;   //相似度算法

    while (1)
    {
        cap >> frame;

        if (cnt == 0)
        {
            Rect2d r;
            r = selectROI(frame, true);
            tempMat = frame(r);
            tempMat.copyTo(refMat);
            destroyAllWindows();            //销毁所有窗口
            cnt++;
        }
        //imshow("ref",refMat);

        //模板匹配函数
        //TM_SQDIFF=0;TM_SQDIFF_NORMED=1;
        //TM_CCORR=2;TM_CCORR_NORMED=3;TM_CCOEFF=4;TM_CCOEFF_NORMED=5
        matchTemplate(frame, refMat, resultMat, match_method);

        //归一化
        normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

        double minVal, maxVal;
        Point minLoc, maxLoc;
        Point matchLoc;
        //寻找极值
        minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        //匹配方式是TM_SQDIFF或TM_SQDIFF_NRMED则匹配数值越低匹配效果越好
        //另外四种则匹配数值越大匹配效果越好
        matchLoc = minLoc;

        //绘制匹配结果图像矩阵
        frame.copyTo(dispMat);
        rectangle(dispMat, matchLoc, Point(matchLoc.x+refMat.cols, matchLoc.y+refMat.rows), Scalar(0,255,0), 2, 8, 0);

        imshow("dispMat", dispMat);
        waitKey(30);
    }

    return 0;
}
