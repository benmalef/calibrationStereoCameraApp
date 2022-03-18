#ifndef STEREOCAMERA_H
#define STEREOCAMERA_H
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;
/// The StereoCamera class
///
/// use the left and the right camera.
class StereoCamera
{
private:

    VideoCapture capLeft;
    VideoCapture capRight;
public:

    StereoCamera();
    ///Creates the paths for the cameras
    /// @param pathCamLeft is the path for the Left Camera
    /// @param pathCamRight is the path for the Rigth Camera
    /// @attention Run on terminal this command to see the correct paths for the cameras: **v4l2-ctl --list-devices**
    StereoCamera(string pathCamLeft, string pathCamRight);
    ~StereoCamera();

    //Methods

    VideoCapture getCapLeft() const;
    void setCapLeft(const VideoCapture &value);
    VideoCapture getCapRight() const;
    void setCapRight(const VideoCapture &value);


    ///Check if the StereoCamera is opened
    bool isOpened();

};

#endif // STEREOCAMERA_H
