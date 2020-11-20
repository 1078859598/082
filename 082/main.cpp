#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat BinaryMat;
	cv::Mat gray;
	cv::Mat openMat;
	cv::Mat Result;


	cv::Mat srcMat = imread("C:/Users/HS/Desktop/2.jpg");
	srcMat.copyTo(Result);

	cvtColor(srcMat, gray, COLOR_BGR2GRAY);
	threshold(gray, BinaryMat, 0, 255, THRESH_OTSU);

	Mat elemt = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(BinaryMat, openMat, MORPH_OPEN, elemt);

	vector<vector<Point>> contours;
	findContours(openMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		cv::Point2f vertex[4];
		rbox.points(vertex);
		float width = rbox.size.width;
		float height = rbox.size.height;
		float pixel = width*height;

		if (pixel > 50 * 50)
		{
			drawContours(Result, contours, i, Scalar(0, 0, 255), 1, 8);
			for (int j = 0; j < 4; j++)
			{
				cv::line(Result, vertex[j], vertex[(j + 1) % 4], Scalar(255, 255, 0), 1, LINE_AA);
			}
		}
	}
	imshow("out", Result);
	imshow("src", srcMat);
	waitKey(0);

}