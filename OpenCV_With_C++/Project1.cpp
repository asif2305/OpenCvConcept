// Virtual Paint
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

/// <summary>
///  ///// Project 1 //////////////////
/// </summary>
Mat img;
vector<vector<int>> newPoints;
vector<vector<int>> myColor{
	{124,48,117,143,170,255} // purple
	,{68,72,156,102,126,255},	// green
	{0,62,0,35,255,255} // orange
	
};
// let define the color value
vector<Scalar> myColorVal = { {255,0,255}, // purple
							 {0, 255 ,0}, // green
							  { 51, 153, 255 }}; // orange

Point getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255),2);

	// We will find out the area of the contour and filter 
	vector<vector< Point>> conPoly(contours.size()); // to find the corner point of the shape
	vector<Rect> boundRect(contours.size());

	Point myPoint(0, 0);
	for (int i = 0;i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		//	cout << area << endl;

		string objectType;
		if (area > 1000) {
			// find the bounding box of the shape
			float peri = arcLength(contours[i], true);
			cout << peri << endl;
			// find the corner point of the polygon
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly.size() << endl;
			// bounding box
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

		    drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

		}
	}
	return myPoint;

}

vector<vector<int>> findColor(Mat img) {
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
  
	for(int i=0;i<myColor.size();i++)
	{ 
	// hmin, smin,vmin,hmax,smax,vmax
 	Scalar lower(myColor[i][0], myColor[i][1], myColor[i][2]);
 	Scalar upper(myColor[i][3], myColor[i][4], myColor[i][5]);
	Mat mask;
	inRange(imgHSV, lower, upper, mask);
	//imshow(to_string(i), mask);
	Point myPoint =  getContours(mask);
	if(myPoint.x !=0 && myPoint.y!=0){
	  newPoints.push_back({ myPoint.x,myPoint.y,i });
	}

	}
	return newPoints;

}
void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorVal) {
	for (int i = 0;i < newPoints.size();i++) {
		circle(img, (Point(newPoints[i][0],newPoints[i][1])),10, myColorVal[newPoints[i][2]], FILLED);
	}
}
void main() {


	VideoCapture cap(0);
	

	while (true) {

		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorVal);
		imshow("Image", img);
		waitKey(1);


	}



}

