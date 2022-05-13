#include<iostream>
#include<opencv2/opencv.hpp>
#include<fstream>
#include<opencv2/dnn.hpp>
#include<opencv2/dnn/all_layers.hpp>
#include<vector>
using namespace std;
using namespace cv;
using namespace dnn;

int main() {
	//load the COCO class names
	vector<string> class_name;
	ifstream ifs(string("Resources/SSMD/label.txt").c_str());
	string line;
	while (getline(ifs, line)) {
		class_name.push_back(line);

	}
	// load the DNN model
	auto model = readNet("Resources/SSD_MobileNet/frozen_inference_graph.pb",
		"Resources/SSD_MobileNet/ssd_mobilenet_v2_coco_2018_03_29.pbtxt.txt", "TensorFlow");
	/*
		auto model = readNetFromCaffe("Resources/SSMD/MobileNetSSD_deploy.prototxt",
			"Resources/SSMD/MobileNetSSD_deploy.caffemodel");
	*/


	// read the image from disk
	//Mat img = imread("Resources/detection.jpg");
	/*
	 // capture the video
	VideoCapture cap("Resources/video_1.mp4");
	// get the video frames' width and height for proper saving of videos
	int frame_width = static_cast<int>(cap.get(3));
	int frame_height = static_cast<int>(cap.get(4));
	// create the `VideoWriter()` object
	VideoWriter out("video_result.avi", VideoWriter::fourcc('M','J','P','G'),30,Size(frame_width, frame_height));
	*/
	// open the camera
	VideoCapture cap(0);

	// set a minimum confidence score for the detections
	float min_confidence_score = 0.5;


	while (cap.isOpened()) {
		Mat img;
		bool isSuccess = cap.read(img);
		if (!isSuccess) break;

		int img_height = img.cols;
		int img_weight = img.rows;

		auto start = getTickCount();

		// Create blob from image
		Mat blob = blobFromImage(img, 1.0, Size(300, 300), Scalar(127.5, 127.5, 127.5), true, false);
		model.setInput(blob);
		// forward pass through the model to carry out the detection
		Mat output = model.forward();
		//Here, index position 1 contains the class label, which can be from 1 to 80.
		//Index position 2 contains the confidence score.This is not a probability score 
		// but rather the model’s confidence for the object belonging to the class that it has detected.
		// Of the final four values, the first two are x, y bounding box coordinates, 
		// and the last is the bounding box’s widthand height.
		auto end = getTickCount();
		// matrix with all direction
		Mat detection(output.size[2], output.size[3], CV_32F, output.ptr<float>());
		// run through all the prediction

		for (int i = 0; i < detection.rows;i++) {
			int class_id = detection.at<float>(i, 1);
			float confidence = detection.at<float>(i, 2);

			// check if the detection is of good condition
			if (confidence > 0.4) {
				// get the bounding box coordinates
				int box_x = static_cast<int>(detection.at<float>(i, 3) * img.cols);
				int box_y = static_cast<int>(detection.at<float>(i, 4) * img.rows);
				// get the bounding box widthand height
				int box_width = static_cast<int>(detection.at<float>(i, 5) * img.cols - box_x);
				int box_height = static_cast<int>(detection.at<float>(i, 6) * img.rows - box_y);

				// draw a rectangle around each detected object
				rectangle(img, Point(box_x, box_y), Point(box_x + box_width, box_y + box_height), Scalar(255, 255, 255), 2);

				// put the FPS text on top of the frame

				putText(img, class_name[class_id - 1] + " " + to_string(int(confidence * 100)) + "%", Point(box_x, box_y - 5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255), 1);
			}
		}
		auto totalTime = (end - start) / getTickFrequency();
		cout << "time" << totalTime << endl;
		putText(img, "FPS: " + to_string(int(1 / totalTime)), Point(50, 50), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0), 2, false);
		imshow("image ", img);

		int k = waitKey(10);

		if (k == 113) {
			break;
		}


	}
	cap.release();
	destroyAllWindows();


}
