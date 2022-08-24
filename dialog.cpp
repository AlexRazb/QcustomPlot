#include "dialog.h"
#include "ui_dialog.h"
#include "qcustomplot.h"
#include "thread.h"


QVector<double> Ax,Ay;
Thread t1;
int CreateRandomVectors(QVector<double> *A,QVector<double> *B);//прототип
int PrintGraph(QCustomPlot *customPlot, QVector<double> &Ax, QVector<double> &Ay);//прототип

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(500, 500));
    customPlot = new QCustomPlot(); // графическое
    ui->gridLayout->addWidget(customPlot,0,0,1,1);  //customPlot в окно проложения

    connect(&t1,&Thread::LetsPrint,this,&Dialog::PrintIt);

    /*шрифт*/
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    /*имена осей*/
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0,20);
    customPlot->yAxis->setRange(0,20);

    /*шаг графика*/
    QSharedPointer<QCPAxisTickerFixed> fixedTicker(new QCPAxisTickerFixed);
    customPlot->xAxis->setTicker(fixedTicker);
    customPlot->yAxis->setTicker(fixedTicker);
    fixedTicker->setTickStep(1.0); // tick step shall be 1.0
    fixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);

    t1.SetCPlot(customPlot);

}

/*слот*/
void Dialog::PrintIt()
{
    customPlot->replot();
}

int PrintGraph(QCustomPlot *customPlot, QVector<double> &Ax, QVector<double> &Ay)
{

    customPlot->clearGraphs();
    /*добавить граф*/
    customPlot->addGraph();
    /*данные в граф*/
    customPlot->graph(0)->setData(Ax,Ay);
    /*добавить линии*/
    customPlot->graph(0)->setPen(QColor(0, 0, 255, 255));//задать цвет линии
    //customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);//убрать линии

    //вид точек
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QColor(255, 0, 0, 255),QColor(255, 0, 0, 255),7));

    /*перерисовать*/
    customPlot->replot();
    return 0;
}

/*заполнить рандомными числами векторы*/
int CreateRandomVectors(QVector<double> *A,QVector<double> *B)
{
    A->clear();
    B->clear();

    for(int i=0;i<15;++i)
    {
        *A << std::rand() % 20;
        *B << std::rand() % 20;
    }

    return 0;
}



Dialog::~Dialog()
{
    if(t1.isRunning()) t1.stop();
    t1.wait();
    delete ui;
}



void Dialog::on_pushButton_start_clicked()
{
    if(t1.isRunning()) t1.resume();

    t1.start();
}


void Dialog::on_pushButton_stop_clicked()
{

     if(t1.isRunning()) t1.stop();

}


void Dialog::on_pushButton_pause_clicked()
{
     if(t1.isRunning()) t1.pause();
}

