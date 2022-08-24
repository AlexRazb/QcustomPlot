#include "thread.h"
#include "dialog.h"

extern QCustomPlot *customPlot;

Thread::Thread(QObject *parent) : QThread(parent), pauseT(false)
{

}

void Thread::pause()
{
    mu.lock();
    if(pauseT == 0)
    {
        pauseT = true;
        mu.unlock();
        return;
    }
    mu.unlock();
}

void Thread::resume()
{
    mu.lock();
    if(pauseT)
    {
        pauseT = false;
        mu.unlock();
        WCond.wakeAll();
        return;
    }
    mu.unlock();
}

/*заполнить рандомными числами векторы*/
int Thread::CreateRandomVectors(QVector<double> *A,QVector<double> *B)
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

int Thread::PrintGraph(QCustomPlot *customPlot, QVector<double> &Ax, QVector<double> &Ay)
{

    if(customPlot->graphCount()) customPlot->clearGraphs();
    /*добавить граф*/
    customPlot->addGraph();
    /*данные в граф*/
    customPlot->graph(0)->setData(Ax,Ay);
    /*добавить линии*/
    customPlot->graph(0)->setPen(QColor(0, 0, 255, 255));//задать цвет линии


    //вид точек
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,QColor(255, 0, 0, 255),QColor(255, 0, 0, 255),7));

    /*перерисовать*/
    emit LetsPrint();

    return 0;
}

void Thread::SetCPlot(QCustomPlot *customPlot1)
{
    customPlot = customPlot1;
    return;
}

void Thread::stop()
{
    WCond.wakeAll();
    mu.lock();
    stopT = true;
    mu.unlock();
}

void Thread::clear()
{
    if(customPlot->graphCount())
    {
        customPlot->graph(0)->data()->clear();
        emit LetsPrint();
        customPlot->clearGraphs();
    }
}


void Thread::run()
{
    pauseT=0;
    stopT =0;
    while(1)
    {
        mu.lock();
        if(pauseT) WCond.wait(&mu);
        if(stopT)
        {
            clear();
            stopT = false;
            mu.unlock();
            break;
        };
        mu.unlock();
        CreateRandomVectors(&A,&B);
        PrintGraph(customPlot,A,B);
        msleep(200);
    }
}
