#include <QToolBox>
#include <QListWidget>
#include <QVBoxLayout>
#include "moduleloader.h"
#include "formalgorithmmenu.h"

FormAlgorithmMenu::FormAlgorithmMenu(QWidget *parent)
    : QWidget(parent),
      m_toolBox(new QToolBox(this))
{
    // 初始化垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    // 初始化抽屉式工具栏
    QListWidget *pages[N_MAX_GROUPS];
    const int npages = ModuleLoader::instance().getGroupsNum();
    for(int i=0;i<npages;++i) {
        pages[i] = new QListWidget(this);
    }
    for(int i=0;i<npages; ++i) {
        m_toolBox->addItem(pages[i], QIcon(":/new/icons/assets/algogroup.png"), ModuleLoader::instance().getGroupText(i));
    }
    layout->addWidget(m_toolBox);

    // 初始化窗体栏
    this->setWindowTitle("Select a Algorithm");
}

