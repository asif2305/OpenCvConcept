// Warp Images
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
/// <summary>
///  ///// Warp images ////////////////
/// </summary>
float w = 250, h = 350;
Mat imgWarp, matrix;
void mainWarp() {
	string path = "Resources/cards.jpg";
	Mat img = imread(path); // Mat is a matrix data type
	

	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	Point2f dst[4] = { {0.0f,0.0f},{w, 0.0f},{0.0f, h},{w,h} };
	matrix = getPerspectiveTransform(src, dst);

	warpPerspective(img, imgWarp, matrix, Point(w,h));

	// create circle for the selected  point
	for (int i = 0; i < 4;i++) {

		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	
	}

	imshow("Image", img);
	imshow(" Warp Image", imgWarp);
	waitKey(0);

}