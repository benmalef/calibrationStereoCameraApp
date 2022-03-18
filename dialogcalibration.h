#ifndef DIALOGCALIBRATION_H
#define DIALOGCALIBRATION_H

#include <QDialog>
#include <QFileDialog>
#include "calibrationstereocamera.h"

namespace Ui {
class DialogCalibration;
}

class DialogCalibration : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCalibration(QWidget *parent = nullptr);
    ~DialogCalibration();

private slots:
    void on_btnExit_clicked();

    void on_btnStart_clicked();

    void on_btnSelect_clicked();

private:
    Ui::DialogCalibration *ui;
    String pathCalibrationLeftCamera;
    String pathCalibrationRightCamera;
};

#endif // DIALOGCALIBRATION_H
