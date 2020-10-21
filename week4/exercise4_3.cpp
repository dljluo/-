/* 练习4-3 使用大津法分隔图像，连通域标记后计算原点个数 */
#include <iostream>
#include <opencv2/opencv.hpp>
#define kernelSize 25       //定义结构元素大小
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

    srcMat = imread(".//PCB.jpg",0);    //读取图像并转换成灰度图
    dstMat = 255 - srcMat;              //色调反转
    threshold(dstMat, resultMat, 100, 255, THRESH_BINARY);  //大津法二值化
    kernel = getStructuringElement(MORPH_RECT, Size(kernelSize,kernelSize));  //定义结构元素
    morphologyEx(resultMat, openMat, 2, kernel);  //开运算

    ConnectedNum = connectedComponentsWithStats(openMat,
                                                labels,
                                                stats,
                                                centroids); //连通域标记

    cout << ConnectedNum-1 << endl;
    //cout << stats << endl;    //初步判断kernelSize范围
    imshow("result", resultMat);
    imshow("openMat", openMat);

    waitKey(0);
    return 0;
}
