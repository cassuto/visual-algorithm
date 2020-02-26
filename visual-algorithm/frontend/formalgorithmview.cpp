#include <QLayout>
#include <QGroupBox>
#include <QSizePolicy>
#include "models.h"
#include "formalgorithmview.h"

FormAlgorithmView::FormAlgorithmView(IModule *module, IModel *model, QWidget *parent)
    : QWidget(parent),
      m_module(module),
      m_model(model)
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
    groupPage[0]->setStretch(0, 0);
    groupPage[0]->setStretch(1, 1);
    groupPage[1]->addWidget(m_outputWidget);
    for(int i=0;i<2;++i) {
        groupBox[i]->setLayout(groupPage[i]);
        layout->addWidget(groupBox[i]);
    }

    this->setWindowTitle(tr("Algorithm View - ") + QString(module->getName()) + "-" + QString(module->getGroup()));
    this->setMinimumSize(QSize(1000,500));
}

void FormAlgorithmView::closeEvent(QCloseEvent *)
{
    emit viewClosed(m_module);
}
