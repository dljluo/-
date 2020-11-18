/* 练习8-1 通过图像形态特征找出轮胎上的圆孔 */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    srcMat = imread("./luntai.png");    //读取图像
    if(srcMat.empty()) return -1;
    imshow("src", srcMat);

    Mat fitMat;
    medianBlur(srcMat, fitMat, 7);      //中值滤波
    //imshow("fitMat", fitMat);

    Mat gryMat;
    cvtColor(fitMat, gryMat, COLOR_RGB2GRAY);   //RGB转灰度图
    //imshow("gryMat", gryMat);

    Mat bnyMat;
    threshold((255-gryMat), bnyMat, 120, 255, THRESH_BINARY);   //二值化
    //imshow("binary", bnyMat);

    Mat kernel;     //结构元素
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(7,7));  //定义结构元素
    morphologyEx(bnyMat, openMat, 2, kernel);               //开运算
    //imshow("openMat", openMat);

    vector<vector<Point>> contours; //轮廓向量
    vector<Vec4i> hierarchy;        //轮廓继承关系
    //寻找连通域
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        double factor;  //圆形度
        //计算圆形度   S=(C^2)/4π
        factor = (contourArea(contours[i]) * 4 * CV_PI) / (pow(arcLength(contours[i], true), 2));
        cout << "factor:" << factor << endl;

        if(factor > 0.8)
        {
            //绘制圆孔
            drawContours(srcMat, contours, i, Scalar(0,255,0), -1, 8);
        }
    }

    imshow("dst", srcMat);
    waitKey(0);
    return 0;
}
