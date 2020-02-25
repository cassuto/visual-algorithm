#include <QToolBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include "moduleloader.h"
#include "mainwindow.h"
#include "formalgorithmview.h"
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
            item->setData(Qt::UserRole, QVariant::fromValue<void*>(mod));
            page->addItem(item);
        }
        m_toolBox->addItem(page, gs);
        // 连接信号槽
        connect(page,SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(menuDbClicked(QListWidgetItem *)));
    }
    layout->addWidget(m_toolBox);

    // 初始化窗体栏
    this->setWindowTitle(tr("Select a Algorithm"));
}

/**
 * @brief FormAlgorithmMenu::menuDbClicked 用户单击工具栏时触发
 * @param item
 */
void FormAlgorithmMenu::menuDbClicked(QListWidgetItem *item)
{
    IModule *module = static_cast<IModule *>(item->data(Qt::UserRole).value<void*>());
    Q_ASSERT(module);

    int status = ModuleLoader::instance().openModule(module);
    switch(status) {
    case VA_OK: // 成功
        {
            FormAlgorithmView *view = new FormAlgorithmView(module);
            MainWindow::instance().workspace().addSubWindow(view);
            connect(view, SIGNAL(viewClosed(IModule *)), this, SLOT(viewClosed(IModule *)));
            view->show();
        }
        break;
    case -VA_OPENED: // 算法已经打开
        QMessageBox::information(this, tr("Open Algorithm"), tr("The algorithm you selected has been opened."), QMessageBox::Ok);
        break;
    default: // 其它
        QMessageBox::critical(this, tr("Load Module"), tr("Failed to load module"), QMessageBox::Ok);
    }
}

/**
 * @brief FormAlgorithmMenu::viewClosed 算法视图关闭时触发
 * @param module
 */
void FormAlgorithmMenu::viewClosed(IModule *module)
{
    ModuleLoader::instance().closeModule(module);
}
