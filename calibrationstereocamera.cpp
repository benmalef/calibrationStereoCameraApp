#include "calibrationstereocamera.h"

CalibrationStereoCamera::CalibrationStereoCamera(
    String pathCalibrationPicturesLeftCamera,
    String pathCalibrationPicturesRightCamera)
    : calibrationPictures(pathCalibrationPicturesLeftCamera,
                          pathCalibrationPicturesRightCamera) {}

CalibrationStereoCamera::~CalibrationStereoCamera()
{

  destroyAllWindows();
}

void CalibrationStereoCamera::findAndStoreChessBoardPoints()
{
  int numOfSuccessPictures = 0;
  int maxNumOfSuccessPictures = 300;

  for (int i{0}; i < this->chessBoardColumns; i++)
  {
    for (int j{0}; j < this->chessBoardRows; j++)
      this->obj.push_back(cv::Point3f(squareSize * j, squareSize * i, 0));
  }

  // Left Camera
  auto calibrationPicturesLeftCamera =
      calibrationPictures.getCalibrationPicturesLeftCamera();
  auto itCalPicLeftCam = calibrationPicturesLeftCamera.begin();
  auto endItCalPicLeftCam = calibrationPicturesLeftCamera.end();
  // Right Camera
  auto calibrationPicturesRigtCamera =
      calibrationPictures.getCalibrationPicturesRightCamera();
  auto itCalPicRightCam = calibrationPicturesRigtCamera.begin();
  auto endItCalPicRightCam = calibrationPicturesRigtCamera.end();

  Size chessBoardSize = Size(chessBoardRows, chessBoardColumns);

  while (itCalPicLeftCam != endItCalPicLeftCam &&
         itCalPicRightCam != endItCalPicRightCam &&
         numOfSuccessPictures < maxNumOfSuccessPictures)
  {

    leftPicture = imread(*(itCalPicLeftCam), IMREAD_GRAYSCALE);
    rightPicture = imread(*(itCalPicRightCam), IMREAD_GRAYSCALE);

    // Left Camera
    bool patternFoundLeftCamera = findChessboardCorners(
        leftPicture, chessBoardSize, cornersLeftCamera,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE +
            CALIB_CB_FAST_CHECK);

    if (patternFoundLeftCamera)
    {
      cornerSubPix(
          leftPicture, cornersLeftCamera, Size(11, 11), Size(-1, -1),
          cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER,
                           30, 0.1));
    }

    // Right Camera
    bool patternFoundRightCamera = findChessboardCorners(
        rightPicture, chessBoardSize, cornersRightCamera,
        CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE +
            CALIB_CB_FAST_CHECK);

    if (patternFoundRightCamera)
    {
      cornerSubPix(
          rightPicture, cornersRightCamera, Size(11, 11), Size(-1, -1),
          cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER,
                           30, 0.1));
    }

    if (patternFoundLeftCamera && patternFoundRightCamera)
    {
      drawChessboardCorners(leftPicture, chessBoardSize, cornersLeftCamera,
                            patternFoundLeftCamera);
      drawChessboardCorners(rightPicture, chessBoardSize, cornersRightCamera,
                            patternFoundRightCamera);
      imagePointsLeftCamera.push_back(cornersLeftCamera);
      imagePointsRightCamera.push_back(cornersRightCamera);
      objectPoints.push_back(obj);
      numOfSuccessPictures++;
    }
    //    imshow("LeftImage", leftPicture);
    //    imshow("RightImage", rightPicture);
    Mat concatImage;
    hconcat(leftPicture, rightPicture, concatImage);
    imshow("Calibrate Images", concatImage);

    waitKey(1000);
    cout << to_string(numOfSuccessPictures) << endl;

    ++itCalPicLeftCam;
    ++itCalPicRightCam;
  }
}

void CalibrationStereoCamera::calibrateEachCamera()
{
  // Calibrate left Camera
  float errorLeftCamera =
      calibrateCamera(objectPoints, imagePointsLeftCamera, leftPicture.size(),
                      mtxL, distL, R_L, T_L);
  new_mtxL = getOptimalNewCameraMatrix(mtxL, distL, leftPicture.size(), 1,
                                       leftPicture.size(), 0);
  cout << "Project Error Left Camera : " << errorLeftCamera << endl;

  float errorRightCamera =
      calibrateCamera(objectPoints, imagePointsRightCamera, rightPicture.size(),
                      mtxR, distR, R_R, T_R);
  new_mtxR = getOptimalNewCameraMatrix(mtxR, distR, rightPicture.size(), 1,
                                       rightPicture.size(), 0);
  cout << "Project Error Right Camera : " << errorRightCamera << endl;
}

void CalibrationStereoCamera::calibrateStereoCamera()
{
  int flag = 0;
  flag |= cv::CALIB_FIX_INTRINSIC;

  float error = stereoCalibrate(
      objectPoints, imagePointsLeftCamera, imagePointsRightCamera, new_mtxL,
      distL, new_mtxR, distR, leftPicture.size(), Rot, Trns, Emat, Fmat, flag,
      cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30,
                       1e-6));
  cout << "The stereo calibration error : " << error << endl;

  stereoRectify(new_mtxL, distL, new_mtxR, distR, rightPicture.size(), Rot,
                Trns, rect_l, rect_r, proj_mat_l, proj_mat_r, Q, 1);
}

void CalibrationStereoCamera::UndistortRectifyMap()
{
  // left Camera
  initUndistortRectifyMap(new_mtxL, distL, rect_l, proj_mat_l, leftPicture.size(), CV_16SC2, leftStereoMapX, leftStereoMapY);
  // right Camera
  initUndistortRectifyMap(new_mtxR, distR, rect_r, proj_mat_r, rightPicture.size(), CV_16SC2, rightStereoMapX, rightStereoMapY);
}

void CalibrationStereoCamera::saveFile()
{
  FileStorage cvFile = FileStorage("calibrationParameters.xml", FileStorage::WRITE);
  cvFile.write("leftStereoMapX", leftStereoMapX);
  cvFile.write("leftStereoMapY", leftStereoMapY);
  cvFile.write("rightStereoMapX", rightStereoMapX);
  cvFile.write("rightStereoMapY", rightStereoMapY);
  cvFile.write("Q", Q);
  cvFile.release();
}

int CalibrationStereoCamera::getSquareSize() const
{
  return squareSize;
}

void CalibrationStereoCamera::setSquareSize(int value)
{
  squareSize = value;
}

int CalibrationStereoCamera::getChessBoardRows() const
{
  return chessBoardRows;
}

void CalibrationStereoCamera::setChessBoardRows(int value)
{
  chessBoardRows = value;
}

int CalibrationStereoCamera::getChessBoardColumns() const
{
  return chessBoardColumns;
}

void CalibrationStereoCamera::setChessBoardColumns(int value)
{
  chessBoardColumns = value;
}
void CalibrationStereoCamera::executeCaibrationStereoCamera()
{
  cout << "Start Calibration Process..." << endl;

  findAndStoreChessBoardPoints();

  calibrateEachCamera();

  calibrateStereoCamera();

  UndistortRectifyMap();

  saveFile();
}

template <class T>
void CalibrationStereoCamera::printAllPoint(const vector<T> &points)
{
  for (auto const &point : points)
  {
    cout << point << endl;
  }
}
