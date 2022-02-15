//License plate Detection
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

#include<iostream>
using namespace cv;
using namespace std;
/// <summary>
///  ///// License plate Detection ////////////////
/// </summary>
void main() {
	VideoCapture cap(0);
	Mat img;

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) {
		cout << "XML file not loaded" << endl;
	}

	// we need to store the bounding box
	vector<Rect> plates;

	while (true) {

		cap.read(img);

		plateCascade.detectMultiScale(img, plates, 1.1, 10);
		// detect all faces
		for (int i = 0; i < plates.size();i++) {
			Mat imgCrop = img(plates[i]);
			//imshow(to_string(i), imgCrop);
			imwrite("Resources/plates/" + to_string(i) + ".png", imgCrop);
			rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3); // FILLED is thickness
		}

		imshow("Image", img);
		waitKey(1);


	}

	

}
