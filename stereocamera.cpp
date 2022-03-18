#include "stereocamera.h"

VideoCapture StereoCamera::getCapLeft() const { return capLeft; }

void StereoCamera::setCapLeft(const VideoCapture &value) { capLeft = value; }

VideoCapture StereoCamera::getCapRight() const { return capRight; }

void StereoCamera::setCapRight(const VideoCapture &value) { capRight = value; }

bool StereoCamera::isOpened()
{
  if (capLeft.isOpened() && capRight.isOpened())
  {
    return true;
  }
  return false;
}

StereoCamera::StereoCamera()
{
  capLeft.open("/dev/video0");
  capRight.open("/dev/video2");
}
StereoCamera::StereoCamera(string pathCamLeft, string pathCamRight)
{
  capLeft.open(pathCamLeft);
  capRight.open(pathCamRight);
}

StereoCamera::~StereoCamera()
{
  capLeft.release();
  capRight.release();
  destroyAllWindows();
}
