#include "worker.h"
#include <QThread>

Worker::Worker()
{
    m_thread.reset(new QThread);
    moveToThread(m_thread.get());
}

Worker::~Worker()
{
    QMetaObject::invokeMethod(this, "cleanup");
    m_thread->wait();
}
