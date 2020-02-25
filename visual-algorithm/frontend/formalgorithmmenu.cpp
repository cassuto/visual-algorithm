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
    const QSet<QString> &groups = ModuleLoader::instance().getGroups();
    foreach(const QString &gs, groups) {
        QListWidget *page = new QListWidget(this);
        const QList<IModule *> &modList = ModuleLoader::instance().getModules(gs);
        foreach(IModule *mod, modList) {
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/new/icons/assets/algogroup.png"),mod->getName(),page);
            page->addItem(item);
        }
        m_toolBox->addItem(page, gs);
    }
    layout->addWidget(m_toolBox);

    // 初始化窗体栏
    this->setWindowTitle("Select a Algorithm");
}

