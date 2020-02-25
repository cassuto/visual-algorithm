#include <QPluginLoader>
#include "moduleloader.h"

ModuleLoader *ModuleLoader::m_instance = 0;
// 算法分组 (hardcoded)
const int ModuleLoader::m_ngroups = 3;
const char *ModuleLoader::m_groupText[] = {"贪心算法","分治算法","图论算法","递归算法"};

ModuleLoader::ModuleLoader()
{
    // 扫描并加载算法模块
    QPluginLoader pluginLoader("module-hanoi.dll");
    if (QObject *plugin = pluginLoader.instance()) {
        IModule *module = dynamic_cast<PluginInterface *>(plugin);
    }

}

int ModuleLoader::getGroupsNum() const
{
    return m_ngroups;
}

const char *ModuleLoader::getGroupText(int idx) const {
    return m_groupText[idx];
}
