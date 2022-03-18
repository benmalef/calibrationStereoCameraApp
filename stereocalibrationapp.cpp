#include "stereocalibrationapp.h"
#include "calibrationpictures.h"
StereoCalibrationApp::StereoCalibrationApp(QObject *parent) : QObject(parent)
{

}

void StereoCalibrationApp::startCalibration()
{
    this->calibrationPictures.takeCalibrationImages();
}
