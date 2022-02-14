// Color Detection
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
/// <summary>
///  ///// Color Detection ////////////////
/// </summary>

Mat imgHSV, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

void main() {
	string path = "Resources/lambo.png";
	Mat img = imread(path); // Mat is a matrix data type
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("TrackBar", (640, 200));
	createTrackbar("Hue min", "TrackBar", &hmin, 179);
	createTrackbar("Hue max", "TrackBar", &hmax, 179);
	createTrackbar("Sat min", "TrackBar", &smin, 255);
	createTrackbar("Sat max", "TrackBar", &smax, 255);
	createTrackbar("Val min", "TrackBar", &vmin, 255);
	createTrackbar("Val max", "TrackBar", &vmax, 255);
	while (true) {
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image HSV", imgHSV);
		imshow("Image mask", mask);
		waitKey(1);
	}
	
}
