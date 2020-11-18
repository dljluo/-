/* 练习8-2 通过图像形态特征找出芯片 */
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat srcMat;
    srcMat = imread("./xinpian.jpg");    //读取图像
    if(srcMat.empty()) return -1;
    //imshow("src", srcMat);

    Mat gryMat;
    cvtColor(srcMat, gryMat, COLOR_RGB2GRAY);   //RGB转灰度图
    //imshow("gryMat", gryMat);

    Mat bnyMat;
    threshold(gryMat, bnyMat, 150, 255, THRESH_BINARY);   //二值化
    //imshow("binary", bnyMat);

    Mat kernel;     //结构元素
    Mat openMat;
    kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //定义结构元素
    morphologyEx(bnyMat, openMat, 2, kernel);               //开运算
    //imshow("openMat", openMat);

    vector<vector<Point>> contours; //轮廓向量
    vector<Vec4i> hierarchy;        //轮廓继承关系
    //寻找连通域
    findContours(openMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for(unsigned int i=0; i<contours.size(); i++)
    {
        double hwr;  //长宽比
        RotatedRect rbox = minAreaRect(contours[i]);    //最小外界四边形
        //计算长宽比
        hwr = rbox.size.height / rbox.size.width;
        cout << "长宽比:" << hwr << endl;
        double S;   //面积
        S = rbox.size.height * rbox.size.width;
        cout << "面积" << S << endl;

        //绘制芯片轮廓
        if(hwr > 0.9 &&  hwr < 1.1 && S > 1000)
        {
            //外接四边形轮廓
            Point2f vtx[4];      //定义外接四边形四个顶点
            rbox.points(vtx);    //计算4个顶点的值
            for(unsigned int j=0; j<4; j++)
                line(srcMat, vtx[j], vtx[(j+1)%4], Scalar(255,0,0), 2, CV_AA);
            //芯片轮廓
            drawContours(srcMat, contours, i, Scalar(0,255,0), 1, 8);
        }
    }

    imshow("dst", srcMat);
    waitKey(0);
    return 0;
}
