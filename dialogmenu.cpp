#include "dialogmenu.h"
#include "ui_dialogmenu.h"
#include "visualizerstereocamera.h"

DialogMenu::DialogMenu(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::DialogMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibration Stereo Camera");
}

DialogMenu::~DialogMenu()
{
    delete ui;
}

void DialogMenu::on_btnCalibrationImages_clicked()
{
    Dialog *dialog = new Dialog(this);
    dialog->exec();
}

void DialogMenu::on_btnExit_clicked()
{
    reject();
}

void DialogMenu::on_btnCalibration_clicked()
{
    DialogCalibration *dialogCal = new DialogCalibration(this);
    dialogCal->exec();
}

void DialogMenu::on_btnRemap_clicked()
{
    VisualizerStereoCamera visualizerStereoCamera;
    visualizerStereoCamera.remapShow();
}
