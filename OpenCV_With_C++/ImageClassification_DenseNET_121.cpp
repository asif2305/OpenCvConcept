#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>
#include<opencv2/dnn.hpp>
#include<opencv2/dnn/all_layers.hpp>
#include<vector>
using namespace std;
using namespace cv;
using namespace dnn;

int main(int, char**) {
	// load the COCO class names
	vector<string> class_names;
	ifstream ifs(string("Resources/DENSENET121/label.txt").c_str());
	string line;
	while (getline(ifs, line)) {
		class_names.push_back(line);
	}
	
	// load the neural network
	auto model = readNet("Resources/DENSENET121/DenseNet_161.prototxt",
		                           "Resources/DENSENET121/DenseNet_161.caffemodel", "Caffe");

	// Read the Image and Prepare it for Model Input
	Mat image = imread("Resources/tiger.jpg");
	// create blob from image
	Mat blob = blobFromImage(image, 0.01, Size(224,224), Scalar(104,117,123));
	// set the input blob for the neural network
	model.setInput(blob);
	// forward pass the image blob through the model
	Mat output = model.forward();
	Point classIdPoint;
	double final_prob;
	minMaxLoc(output.reshape(1,1),0, &final_prob,0,&classIdPoint);
	int label_id = classIdPoint.x;
	// print predicted class
	string out_text = format("%s, %.3f", (class_names[label_id].c_str()), final_prob);
	// put the class name text on top of the image
	putText(image, out_text, Point(25, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0),
		2);
	imshow("Image", image);
	//imwrite("Resources/result_image.jpg", image);
	waitKey(0);


	


}
