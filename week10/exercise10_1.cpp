/* 练习10-1  图像傅里叶变换*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int removeFrequnce();
int selectPolygon(cv::Mat srcMat,cv::Mat &dstMat);
int calcVisbalDft(cv::Mat srcMat, cv::Mat & mag, cv::Mat & ph,double & normVal);
int calcDft2Image(cv::Mat src, cv::Mat mag, cv::Mat ph, double normVal, cv::Mat & dstMat);
void on_mouse(int EVENT, int x, int y, int flags, void* userdata);

std::vector<Point> mousePoints;
Point points;

int main()
{
    //开始计时
	double start = static_cast<double>(cvGetTickCount());

    removeFrequnce();
    waitKey(0);

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;
	//等待键盘响应，按任意键结束程序
	system("pause");

    return 0;
}


/*******************************************
1.输入一张图片，计算其可视化的幅值谱
2.再幅值谱图上，通过鼠标选择需要去除的频率
3.去除被选择的信号，然后复原图像
**********************************************/
int removeFrequnce()
{
    cv::Mat srcMatA = imread("./Alice.jpg", 0);
    cv::Mat srcMatB = imread("./Reimu.jpg", 0);
    if (srcMatA.empty()) {
		std::cout << "failed to read imageA!:" << std::endl;
		return -1;
	}
    if (srcMatB.empty()) {
		std::cout << "failed to read imageB!:" << std::endl;
		return -1;
	}

    cv::Mat dstMatA, dstMatB;
	cv::Mat magMatA, magMatB;
	cv::Mat phMatA, phMatB;
	cv::Mat maskMat;
	double normValA, normValB;

	//输出可视化的mag，以及相位谱，以及归一化系数
	calcVisbalDft(srcMatA, magMatA, phMatA, normValA);
    calcVisbalDft(srcMatB, magMatB, phMatB, normValB);

    //在幅值谱上，通过鼠标选择，需要去掉的频率
    selectPolygon(magMatA, maskMat);

    magMatA = magMatA.mul(maskMat);
    magMatB = magMatB.mul(1-maskMat);

	//逆变换
    calcDft2Image(srcMatA, magMatA, phMatA, normValA, dstMatA);
    calcDft2Image(srcMatB, magMatB, phMatB, normValB, dstMatB);

    Mat dst;
    double alpha=0.5;
    addWeighted(dstMatA, alpha, dstMatB, 1-alpha, 0, dst);
    imshow("A", dstMatA);
    imshow("B", dstMatB);
    imshow("dst", dst);

	return 0;
}

int selectPolygon(cv::Mat srcMat, cv::Mat &dstMat)
{

	vector<vector<Point>> contours;
	cv::Mat selectMat;
	cv::Mat m = cv::Mat::zeros(srcMat.size(), CV_32F);

	m = 1;

	if (!srcMat.empty()) {
		srcMat.copyTo(selectMat);
		srcMat.copyTo(dstMat);
	}
	else {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}

	namedWindow("mouseCallback");
	imshow("mouseCallback", selectMat);
	setMouseCallback("mouseCallback", on_mouse, &selectMat);
	waitKey(0);
	destroyAllWindows();
	//计算roi
	contours.push_back(mousePoints);
	if (contours[0].size() < 3) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}

	drawContours(m, contours, 0, Scalar(0), -1);

	m.copyTo(dstMat);

	return 0;
}


/***************************************************************************************
输入一张图片，输出其傅里叶变换后的可视化的幅值谱
同时输出相位谱，和还原归一化时的系数，即最大值
***************************************************************************************/
int calcVisbalDft(cv::Mat srcMat, cv::Mat & mag, cv::Mat & ph, double & normVal)
{
    Mat src = srcMat.clone();
	int m = getOptimalDFTSize(src.rows); //2,3,5的倍数有更高效率的傅里叶变换
	int n = getOptimalDFTSize(src.cols);
	Mat padded;
	//把灰度图像放在左上角,在右边和下边扩展图像,扩展部分填充为0;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	//planes[0]为dft变换的实部，planes[1]为虚部，ph为相位， plane_true=mag为幅值
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat planes_true = Mat_<float>(padded);
	//保存相位（Mat_代表确定了数据类型，访问元素时不需要再指定元素类型）
	ph = Mat_<float>(padded);

	Mat complexImg;
    //多通道complexImg既有实部又有虚部
	merge(planes, 2, complexImg);
	//对上边合成的mat进行傅里叶变换,***支持原地操作***,傅里叶变换结果为复数.通道1存的是实部,通道二存的是虚部
	dft(complexImg, complexImg);
	//把变换后的结果分割到两个mat,一个实部,一个虚部,方便后续操作
	split(complexImg, planes);

	//---------------此部分目的为更好地显示幅值---后续恢复原图时反着再处理一遍-------------------------
	magnitude(planes[0], planes[1], planes_true);//幅度谱mag
	phase(planes[0], planes[1], ph);//相位谱ph
	Mat A = planes[0];
	Mat B = planes[1];
	mag = planes_true;

	mag += Scalar::all(1);//对幅值加1
    //计算出的幅值一般很大，达到10^4,通常没有办法在图像中显示出来，需要对其进行log求解。
	log(mag, mag);

	//取矩阵中的最大值，便于后续还原时去归一化
	minMaxLoc(mag, 0, &normVal, 0, 0);

	//修剪频谱,如果图像的行或者列是奇数的话,那其频谱是不对称的,因此要修剪
	mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));
	ph = ph(Rect(0, 0, mag.cols & -2, mag.rows & -2));
	Mat _magI = mag.clone();
	//将幅度归一化到可显示范围。
	normalize(_magI, _magI, 0, 1, CV_MINMAX);
	//imshow("before rearrange", _magI);

	//显示规则频谱图
	int cx = mag.cols / 2;
	int cy = mag.rows / 2;

	//这里是以中心为标准，把mag图像分成四部分
	Mat tmp;
	Mat q0(mag, Rect(0, 0, cx, cy));
	Mat q1(mag, Rect(cx, 0, cx, cy));
	Mat q2(mag, Rect(0, cy, cx, cy));
	Mat q3(mag, Rect(cx, cy, cx, cy));
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(mag, mag, 0, 1, CV_MINMAX);
	//imshow("原图灰度图", src);
	//imshow("频谱幅度", mag);

	cv::Mat magwrite = mag * 255;
    imwrite("原频谱.jpg", magwrite);

	return 0;
}

int calcDft2Image(cv::Mat src, cv::Mat mag, cv::Mat ph, double normVal, cv::Mat & dstMat)
{
    cv::Mat dst;

    int m = getOptimalDFTSize(src.rows); //2,3,5的倍数有更高效率的傅里叶变换
	int n = getOptimalDFTSize(src.cols);
    Mat padded;
	//把灰度图像放在左上角,在右边和下边扩展图像,扩展部分填充为0;
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));
	//planes[0]为dft变换的实部，planes[1]为虚部，ph为相位， plane_true=mag为幅值
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat planes_true = Mat_<float>(padded);

	Mat complexImg;
	//多通道complexImg既有实部又有虚部

	Mat magwrite = mag * 255;
	imwrite("处理后频谱.jpg", magwrite);

	int cx = mag.cols / 2;
	int cy = mag.rows / 2;
	//前述步骤反着来一遍，目的是为了逆变换回原图
	Mat q00(mag, Rect(0, 0, cx, cy));
	Mat q10(mag, Rect(cx, 0, cx, cy));
	Mat q20(mag, Rect(0, cy, cx, cy));
	Mat q30(mag, Rect(cx, cy, cx, cy));

	Mat tmp;
	//交换象限
	q00.copyTo(tmp);
	q30.copyTo(q00);
	tmp.copyTo(q30);
	q10.copyTo(tmp);
	q20.copyTo(q10);
	tmp.copyTo(q20);

	mag = mag * normVal;//将归一化的矩阵还原
	exp(mag, mag);		//对应于前述去对数
	mag = mag - Scalar::all(1);//对应前述+1
	polarToCart(mag, ph, planes[0], planes[1]);//由幅度谱mag和相位谱ph恢复实部planes[0]和虚部planes[1]
	merge(planes, 2, complexImg);//将实部虚部合并


	//-----------------------傅里叶的逆变换-----------------------------------
	Mat ifft(Size(mag.cols, mag.rows), CV_8UC1);
	//傅里叶逆变换
	idft(complexImg, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, CV_MINMAX);

	Rect rect(0, 0, mag.cols, mag.rows);
	dst = ifft(rect);
	dst = dst * 255;
	dst.convertTo(dstMat, CV_8UC1);
    //imshow("输出图像", dstMat);

	return 0;
}

/****************鼠标响应函数************************************/
void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{

	Mat hh;
	hh = *(Mat*)userdata;
	Point p(x, y);
	switch (EVENT)
	{
        case EVENT_LBUTTONDOWN:
        {
            points.x = x;
            points.y = y;
            mousePoints.push_back(points);
            circle(hh, points, 4, cvScalar(255, 255, 255), -1);
            imshow("mouseCallback", hh);
        }
        break;
	}
}
