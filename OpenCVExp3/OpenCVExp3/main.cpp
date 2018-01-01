#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

string path;
int Threshold = 128;
Mat picture;

void on_Trackbar(int, void*)
{
	vector<vector<Point>> contours;
	Mat bimage = picture >= Threshold;//二值化
	findContours(bimage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);//轮廓提取

	Mat result = Mat::zeros(bimage.size(), CV_8UC3);
	Mat point;

	for (size_t i = 0; i < contours.size(); i++)
	{
		size_t count = contours[i].size();
		if (count >= 6)
		{
			Mat(contours[i]).convertTo(point, CV_32F);
			RotatedRect box = fitEllipse(point);//椭圆拟合
			ellipse(result, box, Scalar(255, 255, 255), 1, CV_AA);//绘制椭圆
		}
	}
	imshow("result", result);
	imwrite(path + "\\" + "ellipse.png", result);
}

  
int main( int argc, char** argv )  
{
	path = string(*(argv + 1));
	picture = imread(path, 0);
    if(picture.empty())
        return 0;
	path = path.substr(0, path.find_last_of("\\"));
	imshow("source", picture);
    namedWindow("result");
	createTrackbar("threshold", "result", &Threshold, 255, on_Trackbar);
	on_Trackbar(0, 0);
	waitKey();
    return 0;
}  