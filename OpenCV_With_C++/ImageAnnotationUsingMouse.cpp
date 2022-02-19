#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>

using namespace std;
using namespace cv;
// Points to store the bounding box coordinates
Point top_left_corner, bottom_right_corner;
// image
Mat image, temp;

// function which will be called on mouse input
void drawRectangle(int action, int x, int y, int flags, void *userData) {
	// Mark the top left corner when left mouse button is pressed
	if (action == EVENT_LBUTTONDOWN) {
		top_left_corner = Point(x, y);
	}
	// when left mouse is released, mark bottom right corner
	else if (action == EVENT_LBUTTONUP) {
		bottom_right_corner = Point(x, y);
		// Draw Rectangle
		rectangle(image, top_left_corner, bottom_right_corner, Scalar(0,255,0),2,8);
		// Display image
		imshow("Window", image);
	}

 }
// Main function
int mainMouse() {
	image = imread("Resources/annotation.jpg");
	// Make a temporary image, which will be used to clear the image
	temp = image.clone();
	// create a window
	namedWindow("Window");
	// highgui function called when mouse events occur
	setMouseCallback("Window", drawRectangle);

	int k = 0;
	while (k != 113) {
		imshow("Window", image);
		k = waitKey(0);
		// If c is pressed, clear the window, using the dummy image
		if (k == 99) {
			temp.copyTo(image);
		}
	}
	destroyAllWindows();
	return 0;
}
