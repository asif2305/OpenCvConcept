// Opencv Drawing shape and text
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;


/// <summary>
///  /////   Drawing shapes and text ////////////////
/// </summary>
void mainDraw() {
	
	// Blank image
	Mat img(512,512, CV_8UC3, Scalar(255,255,255)); // unsigned: 0 - 255, C3: 3 channel ; Scaler is used to defined the color

	// create circle
	circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);

	// Create rectangle
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); // FILLED is thickness

	// draw a line
	line(img, Point(130,300), Point(382, 300), Scalar(255, 255, 255), 2);

	// write text
	putText(img, "OpenCV learning", Point(137, 262), FONT_HERSHEY_DUPLEX, .75, Scalar(0, 69, 255), 2);
	
	imshow("Image", img);
	waitKey(0);

}