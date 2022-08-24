#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <qcustomplot.h>

class Thread : public QThread
{
     Q_OBJECT
private:
    QVector<double> A, B;
    QCustomPlot *customPlot;    // графич
    bool pauseT;
    bool stopT = 0;
    QMutex mu;
    QWaitCondition WCond;
    int PrintGraph(QCustomPlot *customPlot, QVector<double> &Ax, QVector<double> &Ay);
    int CreateRandomVectors(QVector<double> *A,QVector<double> *B);
public:
    explicit Thread(QObject *parent = nullptr);
    void SetCPlot(QCustomPlot *customPlot1);
    void clear();
    void pause();
    void stop();
    void resume();
    void run();
signals:
    void LetsPrint();

};

#endif // THREAD_H
