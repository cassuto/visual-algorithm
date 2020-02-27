#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QThread>
#include <QSemaphore>
#include "icontrol.h"

/**
 * @brief The RunThread class
 * 提供算法的运行环境
 */
class RunThread : public QThread, public IControl
{
    Q_OBJECT
public:
    RunThread(class IModule *module, class IModel *model, QObject *parent = 0);

    /**
     * @brief 在本线程中运行算法
     * @param module
     * @return
     */
    int startAlgorithm();
    void stopAlgorithm();

    inline bool isRunning() const {
        return m_running;
    }
    inline QSemaphore *semaphore() {
        return m_sempNext;
    }

protected:
    void my_sleep(int msec);
    void waitForNextStep();

protected:
    void run();

private:
    class IModule *m_module;
    class IModel *m_model;
    bool m_running;
    QSemaphore *m_sempNext;
};

#endif // RUNTHREAD_H
