// Document Scanner using OpenCV
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <numeric>
using namespace cv;
using namespace std;
/// <summary>
///  ///// Images ////////////////
/// </summary>
Mat imgOriginal, imgGray, imgCanny, imgThreshold, imgBlur, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoint, docPoints;
float width = 420, height = 596;

Mat preProcessing(Mat img) {

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

	dilate(imgCanny, imgDil, kernel);
	//erode(imgDil, imgErode, kernel);

	return imgDil;


}
vector<Point> getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255),2);

	// We will find out the area of the contour and filter 
	vector<vector< Point>> conPoly(contours.size()); // to find the corner point of the shape
	vector<Rect> boundRect(contours.size());

	vector<Point> biggest;

	int maxArea = 0;
	for (int i = 0;i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		//	cout << area << endl;

		string objectType;
		if (area > 1000) {
			// find the bounding box of the shape
			float peri = arcLength(contours[i], true);
			// find the corner point of the polygon
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			// find the biggest contour
			if (area > maxArea && conPoly[i].size() == 4) {
				//drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5);
				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2], conPoly[i][3]};
				maxArea = area;
			}


			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

		}
	}
	return biggest;

}
void drawPoint(vector<Point> points, Scalar color) {

	for (int i = 0;i < points.size();i++) {
		circle(imgOriginal, points[i], 10, color, FILLED);
	
		putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 2, color, 2);
	}
}

vector<Point> reorder(vector<Point> points) {

	vector<Point> newPoints;
	vector<int> sumPoints, subtractPoint;

	for (int i = 0; i < 4;i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subtractPoint.push_back(points[i].x - points[i].y);
	}

	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 0
	newPoints.push_back(points[max_element(subtractPoint.begin(), subtractPoint.end()) - subtractPoint.begin()]); // index 1
	newPoints.push_back(points[min_element(subtractPoint.begin(), subtractPoint.end()) - subtractPoint.begin()]); // index 2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 3
	return newPoints;
}
Mat getWarp(Mat img, vector<Point> points, float w, float h) {
	Point2f src[4] = { points[0],points[1] ,points[2] ,points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w, 0.0f},{0.0f, h},{w,h} };
	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	return imgWarp;
}

void main() {
	string path = "Resources/paper.jpg";
	imgOriginal = imread(path); // Mat is a matrix data type
	//resize(imgOriginal, imgOriginal, Size(),0.5,0.5);

	// preprocessing img
	imgThreshold = preProcessing(imgOriginal);
	// Get Contours - Biggest
	initialPoint = getContours(imgThreshold);
	drawPoint(initialPoint, Scalar(0,0,255));
	docPoints = reorder(initialPoint);
	//drawPoint(docPoints, Scalar(0,255,0));
	// Warp the image

	imgWarp = getWarp(imgOriginal, docPoints, width, height);

	// crop 
	int cropVal = 5;
	Rect roi(cropVal, cropVal,width-(2* cropVal), height-(2* cropVal));
	imgCrop = imgWarp(roi);



	imshow("Image", imgOriginal);
	imshow("Image Threshold", imgThreshold);
	imshow("Image Warp", imgWarp);
	imshow("Image Crop", imgCrop);
	waitKey(0);

}