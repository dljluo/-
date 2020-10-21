/* 练习4-1 对图像进行二值化后分别进行膨胀、腐蚀、开运算和闭运算 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat srcMat;     //原图
    Mat resultMat;  //二值化结果图像
    Mat erodeMat, dilateMat, openMat, closeMat; //形态学运算结果图像
    Mat kernel;     //结构元素

    srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\coin.jpg",0); //读取并转化成灰度图
    threshold(srcMat, resultMat, 100, 255, THRESH_BINARY);  //二值化

    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //定义结构元素
    morphologyEx(resultMat, erodeMat,  0, kernel);  //腐蚀运算
    morphologyEx(resultMat, dilateMat, 1, kernel);  //膨胀运算
    morphologyEx(resultMat, openMat,   2, kernel);  //开运算
    morphologyEx(resultMat, closeMat,  3, kernel);  //闭运算


    imshow("原图的灰度图", srcMat);
    imshow("二值化图像",   resultMat);
    imshow("腐蚀运算图像", erodeMat);
    imshow("膨胀运算图像", dilateMat);
    imshow("开运算图像",   openMat);
    imshow("闭运算图像",   closeMat);

    waitKey(0);
    return 0;
}
