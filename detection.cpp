#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <stdio.h>
#include <time.h>

#include "common.hpp"

#define SCALE 31.0 / 16.0 // Converts real-world cm into opengl dimension
#define FACE_WIDTH 17.0 // Average person face width in cm
#define FOV 0.70 // Camera Field of View in radian

#define SMOOTHING_RANGE 5

int CAM_WIDTH;
int CAM_HEIGHT;

using namespace cv;

VideoCapture cap;
CascadeClassifier cascade;

void detection_init(){
  string cascadeName = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml"; // Haar-like
  // load classifier
  if (!cascade.load(cascadeName)){
    exit(1);
  }
  
  cap.open(0);
  if (!cap.isOpened()){
    exit(1);
  }
  
  Mat tmp;
  cap >> tmp;
  CAM_WIDTH = tmp.cols;
  CAM_HEIGHT = tmp.rows;
}

double average(std::vector<double> *values, double newValue){
  values->push_back(newValue);
  if (values->size() > SMOOTHING_RANGE){
    values->erase(values->begin());
  }
  
  double sum = 0.0;
  for (unsigned i = 0; i < values->size(); ++i){
    sum += values->at(i);
  }
  
  return sum / values->size();
}

void smooth(double &distance, double &shift_x, double &shift_y){
  static std::vector<double> distances;
  static std::vector<double> x_shiftes;
  static std::vector<double> y_shiftes;
  
  distance = average(&distances, distance);
  shift_x = average(&x_shiftes, shift_x);
  shift_y = average(&y_shiftes, shift_y);
}

void calculate_coordinates(Rect face, double scale){
  Point center;
  center.x = saturate_cast<int>((face.x + face.width * 0.5) * scale);
  center.y = saturate_cast<int>((face.y + face.height * 0.4) * scale);
  double distance, shift_x, shift_y;
  
  distance = FACE_WIDTH * CAM_WIDTH / (face.width * scale * 2 * tan(FOV / 2.0) * SCALE);
  shift_x = (center.x - (CAM_WIDTH / 2.0)) * (distance * tan(FOV / 2.0)) / (CAM_WIDTH / 2.0);
  shift_y = shift_x * (center.y - (CAM_HEIGHT / 2.0)) / (center.x - (CAM_WIDTH / 2.0));
  
  smooth(distance, shift_x, shift_y);
  
  Distance = distance;
  ShiftX = shift_x;
  ShiftY = shift_y;
}

void detection(){
  Mat frame, mosaic;
  cap >> frame;
  
  double scale = 6.0;
  
  Mat gray, smallImg(saturate_cast<int>(frame.rows / scale),
		     saturate_cast<int>(frame.cols / scale), CV_8UC1);
  
  // convert to gray scale
  cvtColor(frame, gray, CV_BGR2GRAY);
  
  //scale-down the image
  resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
  equalizeHist(smallImg, smallImg);
  
  vector<Rect> faces;
  
  // multi-scale face searching
  cascade.detectMultiScale(smallImg, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));
  
  // calculate camera view position using biggest found face 
  if (!faces.empty()){
    int biggest_face_index = 0;
    double biggest_face_width = 0;
    for (unsigned i = 1; i < faces.size(); i++){
      if (biggest_face_width > faces[i].width){
	biggest_face_index = i;
	biggest_face_width = faces[i].width;
      }
    }
    calculate_coordinates(faces[biggest_face_index], scale);
  }
}
