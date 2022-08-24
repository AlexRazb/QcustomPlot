#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "qcustomplot.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QCustomPlot *customPlot;
private slots:
    void on_pushButton_pause_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();

public slots:
    void PrintIt();
private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
