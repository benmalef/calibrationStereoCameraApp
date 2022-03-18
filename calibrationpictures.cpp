#include "calibrationpictures.h"

CalibrationPictures::CalibrationPictures(
    String pathCalibrationPicturesLeftCamera,
    String pathCalibrationPicturesRightCamera)
    : pathCalibrationPicturesLeftCamera{pathCalibrationPicturesLeftCamera},
      pathCalibrationPicturesRightCamera{pathCalibrationPicturesRightCamera}
{
  getCalibrationPictures(pathCalibrationPicturesLeftCamera, "leftCamera");
  getCalibrationPictures(pathCalibrationPicturesRightCamera, "rightCamera");
}
CalibrationPictures::CalibrationPictures() {}

CalibrationPictures::~CalibrationPictures()
{
}

void CalibrationPictures::takeCalibrationImages()
{
  StereoCamera stereoCamera(this->pathLeftCamera, this->pathRightCamera);
  Mat frameLeft, frameRight, concatImage;
  bool pressSaveButton{false};
  int numOfSavePictures{0};
  chrono::time_point<chrono::system_clock> start, end;
  std::chrono::duration<double> delta;

  if (!stereoCamera.isOpened())
  {
    cout << "Error the Stereo Camera can't open";
  }
  while (stereoCamera.isOpened())
  {
    stereoCamera.getCapLeft().read(frameLeft);
    stereoCamera.getCapRight().read(frameRight);

    //    imshow("Left_frame", frameLeft);
    //    imshow("Rigth_frame", frameRight);
    hconcat(frameLeft, frameRight, concatImage);
    imshow("Frame", concatImage);
    int k = waitKey(1);
    if ((this->exit == 'q') || (k == 'q'))
    {
      break;
    }
    else if (this->startTakingImages == 's' || k == 's')
    {
      cout << "<----- Start Saving images ----->" << endl;
      pressSaveButton = true;
      startTakingImages = 'o';
      start = chrono::system_clock::now();
    }
    else if (this->startTakingImages == 'e' || k == 'e')
    {
      cout << "<----- End Saving Images ----->" << endl;
      startTakingImages = 'o';
      pressSaveButton = false;
    }

    if (pressSaveButton == true)
    {
      end = chrono::system_clock::now();
      delta = (end - start);
      if (int(delta.count()) == 3)
      {
        saveCalibrationImages(frameLeft, frameRight, numOfSavePictures++);
        start = chrono::system_clock::now();
      }
    }
  }
}

void CalibrationPictures::saveCalibrationImages(const Mat &frameLeft,
                                                const Mat &frameRight,
                                                int numOfPictures)
{
  string filePathLeft = pathCalibrationPicturesLeftCamera + "/imageL" +
                        to_string(numOfPictures) + ".png";
  string filePathRight = pathCalibrationPicturesRightCamera + "/imageR" +
                         to_string(numOfPictures) + ".png";
  imwrite(filePathLeft, frameLeft);
  imwrite(filePathRight, frameRight);
  cout << "Save Image " << numOfPictures << endl;
  this->numOfSavingImages = numOfPictures;
}

void CalibrationPictures::getCalibrationPictures(const string &filePath,
                                                 const string &cameraName)
{
  if (cameraName == "leftCamera")
  {
    String filePathNameLeft = filePath + "/imageL*.png";
    cv::glob(filePathNameLeft, this->calibrationPicturesLeftCamera, false);
  }
  else if (cameraName == "rightCamera")
  {
    String filePathNameRight = filePath + "/imageR*.png";
    cv::glob(filePathNameRight, this->calibrationPicturesRightCamera, false);
  }
  else
  {
    cout << "Error, choose the leftCamera or the rightCamera";
  }
}

void CalibrationPictures::printFileNames(const vector<cv::String> &fileNames)
{
  for (auto const &fileName : fileNames)
  {
    std::cout << std::string(fileName) << std::endl;
  }
  cout << "<-------------------End--------------------->" << endl
       << endl;
}

void CalibrationPictures::printAllFileNames()
{
  cout << "<---- Left Camera's calibration Images ----> " << endl;
  printFileNames(calibrationPicturesLeftCamera);
  cout << "<---- Right Camera's calibration Images ---->" << endl;
  printFileNames(calibrationPicturesRightCamera);
}

char CalibrationPictures::getExit() const
{
  return exit;
}

void CalibrationPictures::setExit(const char &value)
{
  exit = value;
}

char CalibrationPictures::getStartTakingImages() const
{
  return startTakingImages;
}

void CalibrationPictures::setStartTakingImages(char value)
{
  startTakingImages = value;
}

String CalibrationPictures::getPathCalibrationPicturesLeftCamera() const
{
  return pathCalibrationPicturesLeftCamera;
}

void CalibrationPictures::setPathCalibrationPicturesLeftCamera(const String &value)
{
  pathCalibrationPicturesLeftCamera = value;
}

String CalibrationPictures::getPathCalibrationPicturesRightCamera() const
{
  return pathCalibrationPicturesRightCamera;
}

void CalibrationPictures::setPathCalibrationPicturesRightCamera(const String &value)
{
  pathCalibrationPicturesRightCamera = value;
}

String CalibrationPictures::getPathLeftCamera() const
{
  return pathLeftCamera;
}

void CalibrationPictures::setPathLeftCamera(const String &value)
{
  pathLeftCamera = value;
}

String CalibrationPictures::getPathRightCamera() const
{
  return pathRightCamera;
}

void CalibrationPictures::setPathRightCamera(const String &value)
{
  pathRightCamera = value;
}

int CalibrationPictures::getNumOfSavingImages() const
{
  return numOfSavingImages;
}

void CalibrationPictures::setNumOfSavingImages(int value)
{
  numOfSavingImages = value;
}

vector<cv::String>
CalibrationPictures::getCalibrationPicturesLeftCamera() const
{
  return calibrationPicturesLeftCamera;
}

void CalibrationPictures::setCalibrationPicturesLeftCamera(
    const vector<cv::String> &value)
{
  calibrationPicturesLeftCamera = value;
}

vector<cv::String>
CalibrationPictures::getCalibrationPicturesRightCamera() const
{
  return calibrationPicturesRightCamera;
}

void CalibrationPictures::setCalibrationPicturesRightCamera(
    const vector<cv::String> &value)
{
  calibrationPicturesRightCamera = value;
}
