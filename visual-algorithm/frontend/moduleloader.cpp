#include <QPluginLoader>
#include <QDebug>
#include "module.h"
#include "moduleloader.h"

ModuleLoader *ModuleLoader::m_instance = 0;

ModuleLoader::ModuleLoader()
{
    // 扫描并加载算法模块
    QList<QString> moduleFilenames;
    moduleFilenames.append("../../module-hanoi/debug/module-hanoi.dll");

    foreach(QString fn, moduleFilenames) {
        QPluginLoader pluginLoader(fn);
        if (QObject *plugin = pluginLoader.instance()) {
            IModule *module = dynamic_cast<IModule *>(plugin);
            const char *group = module->getGroup();
            m_groups.insert(group);
            m_modules[group].append(module);
            qDebug() << "ModuleLoader: loaded '" << fn << "':" << module->getName() << "\n";
        } else {
            qDebug()<<"ModuleLoader: Failed to load module '" << fn <<"'\n";
        }
    }
}

const QSet<QString> &ModuleLoader::getGroups() const
{
    return m_groups;
}

const QList<class IModule *> &ModuleLoader::getModules(const QString &group) const
{
    QMap<QString, QList<class IModule *> >::const_iterator it = m_modules.find(group);
    return *it;
}
