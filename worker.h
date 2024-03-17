#ifndef WORKER_H
#define WORKER_H
#include <memory>
#include <QThread>
#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker();

    ~Worker();

signals:
    //int sendSignal;

public slots:
    //void cleanUp();
    //void passData();

private:
    std::unique_ptr<QThread> m_thread;

};

#endif // WORKER_H
