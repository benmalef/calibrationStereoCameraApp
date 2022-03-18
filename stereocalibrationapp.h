#ifndef STEREOCALIBRATIONAPP_H
#define STEREOCALIBRATIONAPP_H

#include <QObject>
#include "calibrationpictures.h"

class StereoCalibrationApp : public QObject
{
    Q_OBJECT
public:
    explicit StereoCalibrationApp(QObject *parent = nullptr);



signals:

private slots:
    void  startCalibration();

private:
    CalibrationPictures calibrationPictures;
};

#endif // STEREOCALIBRATIONAPP_H
