#include "dialogcalibration.h"
#include "ui_dialogcalibration.h"

DialogCalibration::DialogCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCalibration)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibration");
}

DialogCalibration::~DialogCalibration()
{
    delete ui;
}

void DialogCalibration::on_btnExit_clicked()
{
    reject();
}

void DialogCalibration::on_btnStart_clicked()
{
 CalibrationStereoCamera calibrationStereoCamera(this->pathCalibrationLeftCamera,this->pathCalibrationRightCamera);
    int numOfColumns =ui->txtColumns->text().toInt();
    int numOfRows = ui->txtRows->text().toInt();
    int squareSize = ui->txtSquareSize->text().toInt();

calibrationStereoCamera.setChessBoardColumns(numOfColumns);
calibrationStereoCamera.setChessBoardRows(numOfRows);
calibrationStereoCamera.setSquareSize(squareSize);
calibrationStereoCamera.executeCaibrationStereoCamera();

}

void DialogCalibration::on_btnSelect_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,tr("open Directory"),"/home", QFileDialog::ShowDirsOnly);
       String pathCalibrationPictures = dirPath.toStdString();
        this->pathCalibrationLeftCamera = pathCalibrationPictures+"/Left";
       this->pathCalibrationRightCamera = pathCalibrationPictures+"/Right";
}
