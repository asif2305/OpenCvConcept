// Read image vedios and webcams
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;
/// <summary>
///  ///// Importing images ////////////////
/// </summary>
void imageRead() {
	string path = "Resources/test.png";
	Mat img = imread(path); // Mat is a matrix data type
	imshow("Image", img);
	waitKey(0);

}

/// <summary>
///  ///// Vedio /////////////////////
/// </summary>
void readImgFromVideo() {

	

	string path = "Resources/test_video.mp4";
	VideoCapture cap(path);
	Mat img;
	
	while (true) {

		cap.read(img);

		imshow("Image", img);
		waitKey(20);


	}


	
}

/// <summary>
///  ///// Webcam //////////////////
/// </summary>
void readImgFromWebcam() {


	VideoCapture cap(0);
	Mat img;

	while (true) {

		cap.read(img);

		imshow("Image", img);
		waitKey(1);


	}



}

