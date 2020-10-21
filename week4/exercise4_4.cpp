/* 练习4-4 计算图像内回形针数目 */
#include <iostream>
#include <opencv2/opencv.hpp>
#define kernelSize 5        //定义结构元素大小
#define clipSize 400        //定义回形针连通域外接四边形长宽阈值，用于区分前景和背景

using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;         //原图
    Mat dstMat;         //原图色调反转后的图像
    Mat resultMat;      //二值化结果图像
    Mat openMat;        //开运算结果图像
    Mat kernel;         //结构元素
    Mat labels, stats, centroids;   //连通域标签号、状态矩阵、中心矩阵
    int ConnectedNum;   //连通域数量
    int backgroundNum=0;  //背景数量

    srcMat = imread(".\\clip.jpg",0);   //读取图像并转换成灰度图
    dstMat = 255 - srcMat;              //色调反转
    threshold(dstMat, resultMat, 100, 255, THRESH_BINARY);  //大津法二值化
    kernel = getStructuringElement(MORPH_RECT, Size(kernelSize,kernelSize));  //定义结构元素
    morphologyEx(resultMat, openMat, 2, kernel);  //开运算

    ConnectedNum = connectedComponentsWithStats(openMat,
                                                labels,
                                                stats,
                                                centroids); //连通域标记

    for(int i=0; i<ConnectedNum; i++)       //区分前景和背景连通域
    {
        if(stats.at<int>(i,CC_STAT_WIDTH)>clipSize || stats.at<int>(i,CC_STAT_HEIGHT)>clipSize)
            backgroundNum++;
    }

    cout << ConnectedNum-backgroundNum << endl;
    //cout << stats << endl;    //初步预估clipSize值
    imshow("resultMat", resultMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}
