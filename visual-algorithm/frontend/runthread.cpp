#include <QEventLoop>
#include <QTimer>
#include "imodule.h"
#include "runthread.h"

RunThread::RunThread(IModule *module, IModel *model, QObject *parent)
    : QThread(parent),
      m_module(module),
      m_model(model),
      m_running(false),
      m_timeinval(100),
      m_sempNext(0)
{
}

/**
 * @brief 在本线程中运行算法
 * @return
 */
int RunThread::startAlgorithm()
{
    if(!m_running) {
        m_running = true;
        m_sempNext = new QSemaphore();
        QThread::start();
        m_module->run(m_model, this);
        //m_sempNext->acquire();
    }
    return 0;
}

void RunThread::stopAlgorithm()
{
    m_sempNext->release();
    QThread::terminate();
    QThread::wait();
    m_running = false;
    delete m_sempNext;
    m_sempNext = 0;
}

void RunThread::my_sleep(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

/**
 * @brief waitForNextStep
 */
void RunThread::waitForNextStep()
{
    //m_sempNext->acquire();
    //m_sempNext->release();
    my_sleep(m_timeinval);
}

void RunThread::run()
{

}
