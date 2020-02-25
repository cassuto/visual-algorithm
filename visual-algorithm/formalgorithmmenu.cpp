#include <QToolBox>
#include "formalgorithmmenu.h"

FormAlgorithmMenu::FormAlgorithmMenu(QWidget *parent)
    : QWidget(parent),
      m_toolBox(new QToolBox(this))
{
    this->setFixedSize(QSize(200,200));
    this->setWindowTitle("Select a Algorithm");

    const int npages = 4;
    QWidget *pages[npages];
    const char *pagesText[npages] = {"贪心算法","分治算法","图论算法","递归算法"};

    for(int i=0;i<npages;++i) {
        pages[i] = new QWidget(this);
    }
    for(int i=0;i<npages; ++i) {
        m_toolBox->addItem(pages[i], QIcon(":/new/icons/assets/algogroup.png"), pagesText[i]);
    }
}

