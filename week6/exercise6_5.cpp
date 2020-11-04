/* ��ϰ6-5 ͼ����� */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat dstMat;     //���ͼ��
    Mat srcMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\lena.jpg", 1);
    Mat grayMat = imread("D:\\Programming\\CC++\\DigitalImageCode\\lena.jpg", 0);
    if(srcMat.empty()) return -1;
    if(grayMat.empty()) return -1;

    Mat mediaMat;   //��ֵ�˲����ͼ��
    medianBlur(grayMat, mediaMat, 3);   //��ֵ�˲�

    Mat binaryMat;  //��ֵ�����ͼ��
    threshold(mediaMat, binaryMat, 240, 255, THRESH_BINARY); //��ֵ��

    Mat canMat;     //��Ե��ȡ���ͼ��
    Canny(255-binaryMat, canMat, 100, 200, 3, false);   //��Ե��ȡ

    //���������г���Ե��������
    int height = grayMat.rows;  //����
    int width = grayMat.cols;   //����
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

    //�任ǰ��������
    const cv::Point2f src_pt[] = {
                                    cv::Point2f( 45,  2),
                                    cv::Point2f(  2,274),
                                    cv::Point2f(313, 43) };
    //�任����������
    const cv::Point2f dst_pt[] = {
                                    cv::Point2f(  0,  0),
                                    cv::Point2f(  0,315),
                                    cv::Point2f(313,  0) };
    //����������
    const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);
    //����任
    warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

    imshow("src", srcMat);
    imshow("dst", dstMat);
    waitKey(0);

    return 0;
}
