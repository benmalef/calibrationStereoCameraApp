#ifndef CALIBRATIONSTEREOCAMERA_H
#define CALIBRATIONSTEREOCAMERA_H

#include "calibrationpictures.h"
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace std;
using namespace cv;

class CalibrationStereoCamera {

public:
  CalibrationStereoCamera();
  CalibrationStereoCamera(String pathCalibrationPicturesLeftCamera,
                          String pathCalibrationPicturesRightCamera);
  ~CalibrationStereoCamera();

  void defineWorldCoordinates3DPoints();

  void executeCaibrationStereoCamera();

  void findAndStoreChessBoardPoints();
  void calibrateEachCamera();
  template <class T> void printAllPoint(const vector<T> &points);
  void calibrateStereoCamera();

  void UndistortRectifyMap();

  void saveFile();
  int getSquareSize() const;
  void setSquareSize(int value);

  int getChessBoardRows() const;
  void setChessBoardRows(int value);

  int getChessBoardColumns() const;
  void setChessBoardColumns(int value);

private:
  vector<vector<Point3f>> objectPoints;
  vector<vector<Point2f>> imagePointsLeftCamera, imagePointsRightCamera;

  vector<Point2f> cornersLeftCamera;
  vector<Point2f> cornersRightCamera;

  vector<Point3f> obj;
  int chessBoardRows = 8 ;
  int chessBoardColumns = 6;
  int squareSize{30};

  CalibrationPictures calibrationPictures;

  Mat leftPicture;
  Mat rightPicture;
  // Left - Right Camera
  Mat mtxL, distL, R_L, T_L;
  Mat mtxR, distR, R_R, T_R;
  Mat new_mtxL, new_mtxR;

  // Stereo Camera
  Mat Rot, Trns, Emat, Fmat;
  Mat rect_l, rect_r, proj_mat_l, proj_mat_r, Q;
  Mat leftStereoMapX, leftStereoMapY;
  Mat rightStereoMapX, rightStereoMapY;


};

#endif // CALIBRATIONSTEREOCAMERA_H
