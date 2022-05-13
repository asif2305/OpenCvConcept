// Import dependencies
#include<iostream>
#include<opencv2/opencv.hpp>
// Using namespaces to nullify use of c::function(); syntax and std::function(); syntax
using namespace std;
using namespace cv;
Mat imgResize;
// Draw a line
void DrawLine(Mat imageLine) {
	Point pointA(150, 15);
	Point pointB(550, 15);
	line(imageLine, pointA, pointB, Scalar(255, 255, 0), 3, 8, 0);
	imshow("Lined image show", imageLine);
	waitKey();
}
void circleImage(Mat img) {

	// define the center of circle
	Point circle_center(332, 263);

	// define the radius of the circle
	int radius = 200;
	circle(img, circle_center, radius, Scalar(0, 0, 255), 3, 8, 0);
	// to filled circle image
	// circle(img, circle_center, radius, Scalar(0, 0, 255), -1, 8, 0);
	// Display Image
	imshow("Circle Image", img);
	waitKey();
}
void rectangleImage(Mat image) {
	// Define the starting and end points for the rectangle
	Point start_point(67,73);
	Point end_point(527,412);
	// Draw a rectangle using the rectangle() function
	rectangle(image,start_point, end_point, Scalar(0,0,255),3,8,0 );
	imshow("Rectangle on Image", image);
	waitKey();

}
void ellipseDraw(Mat image) {
	// define the center point of ellipse
	// define the center of ellipse
	Point ellipse_center(332, 263);
	// define the major and minor axes of the ellipse

	Point axis1(200, 100); // x = height = major and y= weight = minor axes
	Point axis2(200, 100); // x = height = major and y= weight = minor axes
	// Draw an ellipse using the ellipse() function
	//Horizontal
	ellipse(image, ellipse_center, axis1, 0, 0, 360, Scalar(255, 0, 0), 3, 8, 0);
	// Vertical		
	ellipse(image, ellipse_center, axis2, 90, 0, 360, Scalar(0, 0, 255), 3, 8, 0);
	
	// display the output	
	imshow("Ellipses on Image", image);
	waitKey();



}

void putText(Mat img) {
	putText(img, "I am a Happy cat!", Point(50, 350), FONT_HERSHEY_COMPLEX, 1.5, Scalar(250, 225, 100));
	imshow("Text on Image", img);
	waitKey();

}
int main() {
	// Read image
	Mat img = imread("Resources/Cat.jpg");	
	resize(img, imgResize, Size(), 0.5, 0.5); // fx  and fy
	//imwrite("Resources/resizeCatImg.jpg", imgResize);
	// Print Error message if image is null
	if (imgResize.empty()) {
		cout << "Image could not read" << endl;
	}
	// Draw Line on image
	Mat image = imgResize.clone(); // copy is used in Python
	DrawLine(image);

	// Draw a circle using the circle() Function
	
	circleImage(image);

	// Draw rectangle
	rectangleImage(image);
	
	// Draw ellipse
	ellipseDraw(image);

	// Put text
	putText(image);


}
