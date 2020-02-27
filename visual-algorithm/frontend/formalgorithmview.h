#ifndef FORMDATAINPUT_H
#define FORMDATAINPUT_H

#include <QWidget>
#include "imodule.h"
#include "imodel.h"

/**
 * @brief The formdatainput class
 * 算法视图（数据I/O）窗口
 */
class FormAlgorithmView : public QWidget
{
    Q_OBJECT
public:
    explicit FormAlgorithmView(IModule *module, IModel *model, QWidget *parent = 0);

signals:
    void viewClosed(IModule *module);

public slots:
    void slotRunPressed();
    void slotStopPressed();

protected:
    void updateEnables();
    void closeEvent(QCloseEvent *event);

protected:
    IModule *m_module;
    IModel *m_model;
    QWidget *m_inputWidget;
    QWidget *m_outputWidget;
    class QPushButton *m_btnRun;
    class QPushButton *m_btnStop;
    class RunThread *m_runThread;
};

#endif // FORMDATAINPUT_H
