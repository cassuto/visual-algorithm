#include <QToolBox>
#include <QListWidget>
#include <QVBoxLayout>
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
    const int npages = 4;
    QListWidget *pages[npages];
    const char *pagesText[npages] = {"贪心算法","分治算法","图论算法","递归算法"};

    for(int i=0;i<npages;++i) {
        pages[i] = new QListWidget(this);
    }
    for(int i=0;i<npages; ++i) {
        m_toolBox->addItem(pages[i], QIcon(":/new/icons/assets/algogroup.png"), pagesText[i]);
    }
    layout->addWidget(m_toolBox);

    // 初始化窗体栏
    this->setWindowTitle("Select a Algorithm");
}

