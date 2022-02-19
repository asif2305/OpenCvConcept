// Import dependencies
#include<iostream>
#include<opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

int maxScale = 100;
int scaleFactor = 1;

string windowName = "Resize Image";
string trackbarValue = "Scale";

// Callback functions
void scaleImage(int, void*){
  // read the image
	Mat image = imread("Resources/annotation.jpg");
	// Get the Scale factor from the trackbar

	double scaleFacDouble = 1 + scaleFactor / 100.0;
	// Set the factor to 1 if becomes 0

	if (scaleFacDouble == 0)
	{
		scaleFacDouble = 0;
	}
	Mat scaleImg;
	// Resize the image
	resize(image, scaleImg,Size(), scaleFacDouble, scaleFacDouble, INTER_LINEAR);
	imshow(windowName, scaleImg);
}
int main() {
	Mat image = imread("Resources/annotation.jpg");
	// Create a window to display results and set the flag to Autosize
	namedWindow(windowName, WINDOW_AUTOSIZE);
	// Create Trackbars and associate a callback function
	createTrackbar(trackbarValue, windowName, &scaleFactor, maxScale, scaleImage);

	// Display image
	imshow(windowName, image);
	waitKey(0);
	destroyAllWindows();

	return 0;
}