/* 练习4-2 对图像进行二值化、连通域标记、绘制连通域外界四边形、计数输出操作 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;         //原图
    Mat resultMat;      //二值化结果图像
    Mat boundingboxMat; //绘制出每个连通域的外界四边形图像
    Mat labels, stats, centroids;   //连通域标签号、状态矩阵、中心矩阵
    int ConnectedNum;   //连通域数量
    cv::Rect rect;

    srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\coin.jpg",0); //读取并转化成灰度图
    srcMat.copyTo(boundingboxMat);
    threshold(srcMat, resultMat, 100, 255, THRESH_BINARY);  //二值化
    ConnectedNum = connectedComponentsWithStats(resultMat,
                                                labels,
                                                stats,
                                                centroids); //连通域标记

    for(int i=1; i<ConnectedNum; i++)           //绘制各连通域的外接四边形
    {
        rect.x = stats.at<int>(i,CC_STAT_LEFT);
        rect.y = stats.at<int>(i,CC_STAT_TOP);
        rect.width = stats.at<int>(i,CC_STAT_WIDTH);
        rect.height = stats.at<int>(i,CC_STAT_HEIGHT);
        rectangle(boundingboxMat, rect, CV_RGB(0,0,255),3,8,0);
    }

    cout << ConnectedNum-1 << endl;             //输出除背景外的连通域个数
    //cout << stats << endl;
    imshow("boundingboxMat", boundingboxMat);
    waitKey(0);
    return 0;
}
