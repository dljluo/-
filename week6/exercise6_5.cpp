/* 练习6-5 图像矫正 */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat dstMat;     //输出图像
    Mat srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\lena.jpg", 1);
    Mat grayMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\lena.jpg", 0);
    if(srcMat.empty()) return -1;
    if(grayMat.empty()) return -1;

    Mat mediaMat;   //中值滤波结果图像
    medianBlur(grayMat, mediaMat, 3);   //中值滤波

    Mat binaryMat;  //二值化结果图像
    threshold(mediaMat, binaryMat, 240, 255, THRESH_BINARY); //二值化

    Mat canMat;     //边缘提取结果图像
    Canny(255-binaryMat, canMat, 100, 200, 3, false);   //边缘提取

    //遍历像素列出边缘像素坐标
    int height = grayMat.rows;  //行数
    int width = grayMat.cols;   //列数
    for(int i=0; i<height; i++)
    {
        uchar* data = canMat.ptr<uchar>(i);
        for(int j=0; j<width; j++)
        {
            if(data[j])
            {
                cout << j << "\t" << i << endl;
            }
        }
    }

    //变换前三点坐标
    const cv::Point2f src_pt[] = {
                                    cv::Point2f( 45,  2),
                                    cv::Point2f(  2,274),
                                    cv::Point2f(313, 43) };
    //变换后三点坐标
    const cv::Point2f dst_pt[] = {
                                    cv::Point2f(  0,  0),
                                    cv::Point2f(  0,315),
                                    cv::Point2f(313,  0) };
    //计算仿射矩阵
    const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);
    //仿射变换
    warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

    imshow("src", srcMat);
    imshow("dst", dstMat);
    waitKey(0);

    return 0;
}
