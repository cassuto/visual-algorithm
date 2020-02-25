#include <QPluginLoader>
#include <QDebug>
#include "imodule.h"
#include "models.h"
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

/**
 * @brief 获取组列表
 * @return reference to QSet
 */
const QSet<QString> &ModuleLoader::getGroups() const
{
    return m_groups;
}

/**
 * @brief 获取组内模块
 * @param group 组名
 * @return reference to QList
 */
const QList<class IModule *> &ModuleLoader::getModules(const QString &group) const
{
    QMap<QString, QList<class IModule *> >::const_iterator it = m_modules.find(group);
    return *it;
}

/**
 * @brief 打开算法模块
 * @param mod 指向算法模块接口的指针
 * @param model [out] 指向存储模型接口指针的指针
 * @return status code
 */
int ModuleLoader::openModule(IModule *module, IModel **model)
{
    if (!m_moduleOpened[module]) {
        *model = ModelFactory::instance().createModel(module->getModelSymbol());
        if(*model == 0l) {
            return -VA_INVALID_MODEL;
        }
        if(int rc = module->open()) {
            return rc;
        }
        m_moduleOpened[module] = true;
        return 0;
    }
    return -VA_OPENED;
}

/**
 * @brief 关闭算法模块
 * @param mod 指向算法模块接口的指针
 */
void ModuleLoader::closeModule(IModule *mod)
{
    mod->close();
    m_moduleOpened[mod] = false;
}
