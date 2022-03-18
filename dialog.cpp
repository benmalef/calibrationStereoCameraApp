#include "dialog.h"
#include "./ui_dialog.h"
#include "calibrationpictures.h"
#include "visualizerstereocamera.h"
#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibration Images");
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    String textPath = ui->txtPathLeftCamera->text().toStdString();
    this->calibrationPictures.setPathLeftCamera(textPath);

    this->calibrationPictures.takeCalibrationImages();
    QString numOfSavingImages = QString::number(this->calibrationPictures.getNumOfSavingImages());
}

void Dialog::on_pushButton_2_clicked()
{
    this->calibrationPictures.setExit('q');
}

void Dialog::on_btnSaveImages_clicked()
{
    this->calibrationPictures.setStartTakingImages('s');
}

void Dialog::on_btnStopSaving_clicked()
{
    this->calibrationPictures.setStartTakingImages('e');
}

void Dialog::on_btnSelectDir_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this,tr("open Directory"),"/home", QFileDialog::ShowDirsOnly);
        //create the folders
    QString dirRightFolder = "Right";
    QString dirLeftFolder = "Left";
    QDir dir(dirPath);
    dir.mkdir(dirRightFolder);
    dir.mkdir(dirLeftFolder);

    String pathCalibrationPictures = dirPath.toStdString();
    this->calibrationPictures.setPathCalibrationPicturesLeftCamera(pathCalibrationPictures+"/Left");
    this->calibrationPictures.setPathCalibrationPicturesRightCamera(pathCalibrationPictures+"/Right");
}
