#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "calibrationpictures.h"
#include "dialog.h"
#include "./ui_dialog.h"
#include "calibrationpictures.h"
#include "visualizerstereocamera.h"
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btnSaveImages_clicked();

    void on_btnStopSaving_clicked();

    void on_btnSelectDir_clicked();

private:
    Ui::Dialog *ui;
    CalibrationPictures calibrationPictures;
};
#endif // DIALOG_H
