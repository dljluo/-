/* 调用2种二值化函数，实现二值化 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat = imread(".//adaptive.png", 0);
    Mat resultMat;
    Mat adaptive_resultMat1,adaptive_resultMat2;

    threshold(srcMat, resultMat, 100, 255, THRESH_BINARY);  //二值化
    adaptiveThreshold(srcMat, adaptive_resultMat1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 17, 10);    //局部自适应二值化
    adaptiveThreshold(srcMat, adaptive_resultMat2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 17, 10);

    imshow("srcMat", srcMat);
    imshow("resultMat", resultMat);
    imshow("adaptive_resultMat1", adaptive_resultMat1);
    imshow("adaptive_resultMat2", adaptive_resultMat2);

    waitKey(0);

    return 0;
}
