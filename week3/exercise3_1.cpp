/* RGB转HSV */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);    //调用摄像头

    double scale = 0.5;     //帧缩放

    //0-180
    //肤色
    double i_minH = 0;
    double i_maxH = 20;
    //0-255
    double i_minS = 43;
    double i_maxS = 255;
    //0-255
    double i_minV = 55;
    double i_maxV = 255;

    while (1)
    {
        Mat frame;
        Mat hsvMat;
        Mat detectMat;

        cap >> frame;
        Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);  //对原图进行缩放
        Mat rFrame = Mat(ResImgSiz, frame.type());
        resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

        cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);    //将原图转成hsv格式

        rFrame.copyTo(detectMat);   //深复制一个原图作显示用

        cv::inRange(hsvMat, Scalar(i_minH,i_minS,i_minV), Scalar(i_maxH,i_maxS,i_maxV), detectMat);

        imshow("while: in the range", detectMat);
        imshow("frame", rFrame);

        waitKey(30);
    }
}
