/* 练习8-3 通过图像形态特征找出茶杯 */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    Mat dstMat;
    srcMat = imread("./cup.jpg");    //读取图像
    if(srcMat.empty()) return -1;
    resize(srcMat, dstMat, Size(srcMat.cols*0.1,srcMat.rows*0.1));  //对原图进行缩小
    imshow("src", dstMat);

    //红色hsv范围
    double i_minHA = 0;
    double i_maxHA = 10;
    double i_minHB = 156;
    double i_maxHB = 180;
    double i_minS = 70;
    double i_maxS = 255;
    double i_minV = 46;
    double i_maxV = 255;

    Mat hsvMat;
    Mat bnyAPart, bnyBPart;
    Mat bnyMat;
    cvtColor(dstMat, hsvMat, COLOR_BGR2HSV);    //将原图转成hsv格式
    //根据颜色特征区分前景背景
    inRange(hsvMat, Scalar(i_minHA,i_minS,i_minV), Scalar(i_maxHA,i_maxS,i_maxV), bnyAPart);
    inRange(hsvMat, Scalar(i_minHB,i_minS,i_minV), Scalar(i_maxHB,i_maxS,i_maxV), bnyBPart);
    bnyMat = bnyAPart + bnyBPart;
    //imshow("A", bnyAPart);
    //imshow("B", bnyBPart);

    Mat kernel;     //结构元素
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //定义结构元素
    morphologyEx(bnyMat, openMat, 2, kernel);               //开运算
    imshow("openMat", openMat);

    vector<vector<Point>> contours; //轮廓向量
    vector<Vec4i> hierarchy;        //轮廓继承关系
    //寻找连通域
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        RotatedRect rbox = minAreaRect(contours[i]);    //最小外界四边形
        double factor;  //圆形度
        //计算圆形度   S=(C^2)/4π
        factor = (contourArea(contours[i]) * 4 * CV_PI) / (pow(arcLength(contours[i], true), 2));
        cout << "factor:" << factor << endl;

        //绘制茶杯外接四边形
        if(factor > 0.8)
        {
            Point2f vtx[4];      //定义外接四边形四个顶点
            rbox.points(vtx);    //计算4个顶点的值
            for(unsigned int j=0; j<4; j++)
                line(dstMat, vtx[j], vtx[(j+1)%4], Scalar(200,0,240), 1, CV_AA);
        }
    }

    imshow("dst", dstMat);
    waitKey(0);
    return 0;
}
