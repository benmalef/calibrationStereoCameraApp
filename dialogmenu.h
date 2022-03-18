#ifndef DIALOGMENU_H
#define DIALOGMENU_H

#include <QDialog>
#include "dialog.h"
#include "dialogcalibration.h"
#include "visualizerstereocamera.h"


namespace Ui {
class DialogMenu;
}

class DialogMenu : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMenu(QWidget *parent = nullptr);
    ~DialogMenu();

private slots:


    void on_btnCalibrationImages_clicked();

    void on_btnExit_clicked();
    void on_btnCalibration_clicked();

 

    void on_btnRemap_clicked();

private:
    Ui::DialogMenu *ui;
};

#endif // DIALOGMENU_H
