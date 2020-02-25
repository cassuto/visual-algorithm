#ifndef ALGORITHMLOADER_H
#define ALGORITHMLOADER_H

#include <QList>
#include <QMap>
#include <QSet>
#include <QString>

#include "module.h"

/**
 * @brief The ModuleLoader class
 * 算法模块装载器
 */
class ModuleLoader
{
public:
    ModuleLoader();

    /**
     * @brief 获取组列表
     * @return reference to QSet
     */
    const QSet<QString> &getGroups() const;
    /**
     * @brief 获取组内模块
     * @param group 组名
     * @return reference to QList
     */
    const QList<class IModule *> &getModules(const QString &group) const;

    /**
     * @brief 打开算法模块
     * @param mod 指向算法模块接口的指针
     * @return status code
     */
    int openModule(IModule *mod);
    /**
     * @brief 关闭算法模块
     * @param mod 指向算法模块接口的指针
     */
    void closeModule(IModule *mod);

    // Singleton Mode
    static ModuleLoader &instance() {
        if(!m_instance) {
            m_instance = new ModuleLoader;
        }
        return *m_instance;
    }

protected:
    QSet<QString> m_groups;
    QMap<QString, QList<IModule *> > m_modules;
    QMap<IModule *,bool> m_moduleOpened;

private:
    static ModuleLoader *m_instance;
};

#endif // ALGORITHMLOADER_H
