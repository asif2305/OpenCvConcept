// Shapes and contour detection
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
/// <summary>
///  ///// Shapes and contour detection ////////////////
/// </summary>
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

/// <Contours>
/// Contours are an outline representing or bounding the shape or form of something.
/// Contours are designed using edges.
/// They are edges with an identity, geometrical parameters and are continuous.
/// They are useful for shape analysis and object recognition.
/// </Contours>
void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255),2);

	// We will find out the area of the contour and filter 
	for (int i = 0;i < contours.size(); i++) {
		int area = contourArea(contours[i]);
	//	cout << area << endl;
		vector<vector< Point>> conPoly(contours.size()); // to find the corner point of the shape
		vector<Rect> boundRect(contours.size());
		string objectType;
		if (area > 1000) {
			// find the bounding box of the shape
			float peri = arcLength(contours[i], true);
			cout << peri << endl;
			// find the corner point of the polygon
			approxPolyDP(contours[i],conPoly[i], 0.02 * peri, true);
			cout << conPoly.size() << endl;
			// bounding box
			boundRect[i] = boundingRect(conPoly[i]);
	    	
			// lets find the specific shape
			int objCor = (int)conPoly[i].size();

			if (objCor == 3) { objectType = "Tri"; }
			if (objCor == 4) { 
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) {
					objectType = "Square";
				}
				else objectType = "Rect";
			}
			if (objCor > 4) { objectType = "Circle"; }

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			// write text
			putText(img, objectType, {boundRect[i].x , boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
		}
	}
	
}

void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path); // Mat is a matrix data type
	// Preprocessing of the image
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	dilate(imgCanny, imgDil, kernel);
	getContours(imgDil, img);
	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dilate", imgDil);
	waitKey(0);

}