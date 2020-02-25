#ifndef MODULEHANOI_H
#define MODULEHANOI_H

#include "module-hanoi_global.h"
#include "module.h"

class MODULEHANOISHARED_EXPORT ModuleHanoi : public QObject, public IModule
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.visualalgorithm.modules.hanoi")
    Q_INTERFACES(IModule)
public:
    ModuleHanoi();

protected:
    // 重载IModule接口
    const char *getName() const;
};

#endif // MODULEHANOI_H
