#include <iostream>
#include<stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;

int main(int, char**) {
  Mat image;
  image = imread("D:/Github Repo/GitHub/OpenCvConcept/water.png", 1);

  if(!image.data){
      printf("No image Data \n");
      return -1;
      
  }
  namedWindow("Display image", WINDOW_AUTOSIZE);
  imshow("Diaplay Image", image);
  waitKey(0);
  return 0;

}
