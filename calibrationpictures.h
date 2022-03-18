#ifndef CALIBRATIONPICTURES_H
#define CALIBRATIONPICTURES_H
#include <chrono>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <string>
#include <time.h>

#include "stereocamera.h"

using namespace cv;
using namespace std;

class CalibrationPictures {
public:
  CalibrationPictures();
  CalibrationPictures(String pathCalibrationPicturesLeftCamera,
                      String pathCalibrationPicturesRightCamera);
  ~CalibrationPictures();

  // Calibration Images
  void takeCalibrationImages();
  void saveCalibrationImages(const Mat &frameLeft, const Mat &frameRight,
                             int numOfPictures);

  void getCalibrationPictures(const string &filePath, const string &cameraName);
  vector<cv::String> getCalibrationPicturesLeftCamera() const;
  void setCalibrationPicturesLeftCamera(const vector<cv::String> &value);

  vector<cv::String> getCalibrationPicturesRightCamera() const;
  void setCalibrationPicturesRightCamera(const vector<cv::String> &value);

  void printFileNames(const vector<cv::String>  &fileNames);
  void printAllFileNames();


  char getExit() const;
  void setExit(const char &value);

  char getStartTakingImages() const;
  void setStartTakingImages(char value);

  String getPathCalibrationPicturesLeftCamera() const;
  void setPathCalibrationPicturesLeftCamera(const String &value);

  String getPathCalibrationPicturesRightCamera() const;
  void setPathCalibrationPicturesRightCamera(const String &value);

  String getPathLeftCamera() const;
  void setPathLeftCamera(const String &value);

  String getPathRightCamera() const;
  void setPathRightCamera(const String &value);

  int getNumOfSavingImages() const;
  void setNumOfSavingImages(int value);

private:
  String pathCalibrationPicturesLeftCamera;
  String pathCalibrationPicturesRightCamera;
  vector<cv::String> calibrationPicturesLeftCamera;
  vector<cv::String> calibrationPicturesRightCamera;
  String pathLeftCamera= "/dev/video0";
  String pathRightCamera= "/dev/video2";
  char exit;
  char startTakingImages;
  int numOfSavingImages;
};

#endif // CALIBRATIONPICTURES_H
