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

    // 创建数据I/O控件
    m_inputWidget = m_model->createInputWidget(this);
    m_outputWidget = m_model->createOutputWidget(this);

    // 初始化界面分组
    QGroupBox *groupBox[2] = {
        new QGroupBox(tr("Data Input"), this),
        new QGroupBox(tr("Data Output"), this),
    };
    QHBoxLayout *groupPage[2] = {
        new QHBoxLayout(),
        new QHBoxLayout()
    };
    groupPage[0]->addWidget(m_inputWidget);
    groupPage[1]->addWidget(m_outputWidget);
    for(int i=0;i<2;++i) {
        groupBox[i]->setLayout(groupPage[i]);
        layout->addWidget(groupBox[i]);
    }

    this->setWindowTitle(tr("Algorithm View - ") + QString(module->getName()) + "-" + QString(module->getGroup()));
}

void FormAlgorithmView::closeEvent(QCloseEvent *)
{
    emit viewClosed(m_module);
}
