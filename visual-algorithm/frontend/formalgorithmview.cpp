#include <QLayout>
#include <QGroupBox>
#include <QSizePolicy>
#include <QPushButton>
#include "models.h"
#include "runthread.h"
#include "formalgorithmview.h"

FormAlgorithmView::FormAlgorithmView(IModule *module, IModel *model, QWidget *parent)
    : QWidget(parent),
      m_module(module),
      m_model(model),
      m_runThread(new RunThread(module, model, this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    // 数据I/O控件
    m_inputWidget = m_model->getInputWidget(this);
    m_outputWidget = m_model->getOutputWidget(this);

    // 初始化界面分组
    QGroupBox *groupBox[3] = {
        new QGroupBox(tr("Data Input"), this),
        new QGroupBox(tr("Data Output"), this),
        new QGroupBox(tr("Control Pannel"), this),
    };
    QVBoxLayout *groupPage[2] = {
        new QVBoxLayout(),
        new QVBoxLayout()
    };
    groupPage[0]->addWidget(m_inputWidget);
    groupPage[0]->addWidget(groupBox[2]);
    groupPage[0]->setStretch(0, 1);
    groupPage[0]->setStretch(1, 0);

    // 初始化控制面板
    QHBoxLayout *ctrlLayout = new QHBoxLayout();
    m_btnRun = new QPushButton(QIcon(":/new/icons/assets/run.png"), tr("Run."),groupBox[2]);
    ctrlLayout->addWidget(m_btnRun);
    m_btnStop = new QPushButton(QIcon(":/new/icons/assets/stop.png"), tr("Stop."),groupBox[2]);
    ctrlLayout->addWidget(m_btnStop);
    groupBox[2]->setLayout(ctrlLayout);

    connect(m_btnRun, SIGNAL(pressed()), this, SLOT(slotRunPressed()));
    connect(m_btnStop, SIGNAL(pressed()), this, SLOT(slotStopPressed()));

    groupPage[1]->addWidget(m_outputWidget);
    for(int i=0;i<2;++i) {
        groupBox[i]->setLayout(groupPage[i]);
        layout->addWidget(groupBox[i]);
    }

    layout->setStretch(0,0);
    layout->setStretch(1,1);

    this->setWindowTitle(tr("Algorithm View - ") + QString(module->getName()) + "-" + QString(module->getGroup()));
    this->setMinimumSize(QSize(1000,500));
}

void FormAlgorithmView::slotRunPressed()
{
    m_runThread->startAlgorithm();
    updateEnables();
}

void FormAlgorithmView::slotStopPressed()
{
    m_runThread->stopAlgorithm();
    updateEnables();
}

void FormAlgorithmView::updateEnables()
{
    if(m_runThread->isRunning()) {
        m_btnRun->setEnabled(false);
        m_btnStop->setEnabled(true);
    } else {
        m_btnRun->setEnabled(true);
        m_btnStop->setEnabled(false);
    }
}

void FormAlgorithmView::closeEvent(QCloseEvent *)
{
    emit viewClosed(m_module);
}
