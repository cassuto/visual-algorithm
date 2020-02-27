#include <QLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QSizePolicy>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QCloseEvent>
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
    QVBoxLayout *layMain = new QVBoxLayout();

    QFormLayout *speedLayout = new QFormLayout();
    m_labTimeInval = new QLabel(groupBox[2]);
    speedLayout->addWidget(m_labTimeInval);
    m_sliderTimeinval = new QSlider(Qt::Vertical, groupBox[2]);
    m_sliderTimeinval->setMaximum(1500);
    m_sliderTimeinval->setMinimum(10);
    m_sliderTimeinval->setTickPosition(QSlider::TicksBelow);
    m_sliderTimeinval->setTickInterval(10);
    speedLayout->addWidget(m_sliderTimeinval);

    QHBoxLayout *ctrlLayout = new QHBoxLayout();
    ctrlLayout->addWidget(m_sliderTimeinval);
    m_btnRun = new QPushButton(QIcon(":/new/icons/assets/run.png"), tr("Run."),groupBox[2]);
    ctrlLayout->addWidget(m_btnRun);
    m_btnStop = new QPushButton(QIcon(":/new/icons/assets/stop.png"), tr("Stop."),groupBox[2]);
    ctrlLayout->addWidget(m_btnStop);

    layMain->addLayout(speedLayout);
    layMain->addLayout(ctrlLayout);
    groupBox[2]->setLayout(layMain);

    connect(m_sliderTimeinval, SIGNAL(valueChanged(int)), this, SLOT(slotTimeinvalChanged(int)));
    connect(m_btnRun, SIGNAL(pressed()), this, SLOT(slotRunPressed()));
    connect(m_btnStop, SIGNAL(pressed()), this, SLOT(slotStopPressed()));

    m_sliderTimeinval->setValue(m_model->getTimeInval());

    groupPage[1]->addWidget(m_outputWidget);
    for(int i=0;i<2;++i) {
        groupBox[i]->setLayout(groupPage[i]);
        layout->addWidget(groupBox[i]);
    }

    layout->setStretch(0,0);
    layout->setStretch(1,1);

    this->setWindowTitle(tr("Algorithm View - ") + QString(module->getName()) + "-" + QString(module->getGroup()));
    this->setMinimumSize(QSize(1000,550));
}

void FormAlgorithmView::slotRunPressed()
{
    m_btnRun->setEnabled(false);
    m_btnStop->setEnabled(true);
    m_inputWidget->setEnabled(false);
    m_runThread->startAlgorithm();
    m_inputWidget->setEnabled(true);
    m_btnRun->setEnabled(true);
    m_btnStop->setEnabled(false);
    //updateEnables();
}

void FormAlgorithmView::slotStopPressed()
{
    //m_runThread->stopAlgorithm();
    //updateEnables();
}

void FormAlgorithmView::slotTimeinvalChanged(int v)
{
    m_labTimeInval->setText(QString(tr("Time Interval (%1 ms):")).arg(v));
    m_runThread->setTimeInval(v);
}

void FormAlgorithmView::updateEnables()
{
    /*if(m_runThread->isRunning()) {
        m_btnRun->setEnabled(false);
        m_btnStop->setEnabled(true);
    } else {
        m_btnRun->setEnabled(true);
        m_btnStop->setEnabled(false);
    }*/
}

void FormAlgorithmView::closeEvent(QCloseEvent *event)
{
    if(!m_runThread->isRunning()) {
        emit viewClosed(m_module);
    } else {
        event->ignore();
    }
}
