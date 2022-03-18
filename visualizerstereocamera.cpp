#include "visualizerstereocamera.h"

VisualizerStereoCamera::VisualizerStereoCamera() {}

VisualizerStereoCamera::VisualizerStereoCamera(string pathCamLeft,
                                               string pathCamRight)
    : stereoCamera(pathCamLeft, pathCamRight) {}

VisualizerStereoCamera::~VisualizerStereoCamera() {}

void VisualizerStereoCamera::show() {
  Mat frameLeft;
  Mat frameRight;
  while (stereoCamera.isOpened()) {
    stereoCamera.getCapLeft().read(frameLeft);
    stereoCamera.getCapRight().read(frameRight);
    imshow("Left Camera", frameLeft);
    imshow("Right Camera", frameRight);
    int k = waitKey(1);
    if (k == 'q') {
      break;
    }
  }
}

void VisualizerStereoCamera::remapShow() {
  Mat leftStereoMapX, leftStereoMapY;
  Mat rightStereoMapX, rightStereoMapY;
  FileStorage cvFile = FileStorage("calibrationParameters.xml", FileStorage::READ);
  cvFile["leftStereoMapX"] >> leftStereoMapX;
  cvFile["leftStereoMapY"] >> leftStereoMapY;
  cvFile["rightStereoMapX"] >> rightStereoMapX;
  cvFile["rightStereoMapY"] >> rightStereoMapY;
  cvFile.release();

  Mat frameLeft;
  Mat frameRight;
  Mat concatImage;
  Mat remapFrameLeft;
  Mat remapFrameRight;
  while (stereoCamera.isOpened()) {
    stereoCamera.getCapLeft().read(frameLeft);
    stereoCamera.getCapRight().read(frameRight);

    remap(frameLeft, remapFrameLeft, leftStereoMapX, leftStereoMapY,
          cv::INTER_LANCZOS4, cv::BORDER_CONSTANT, 0);
    remap(frameRight, remapFrameRight, rightStereoMapX, rightStereoMapY,
          cv::INTER_LANCZOS4, cv::BORDER_CONSTANT, 0);

    hconcat(remapFrameLeft,remapFrameRight,concatImage);
    imshow("Frame", concatImage);

    int k = waitKey(1);
    if (k == 'q') {
      break;
    }
  }
}




