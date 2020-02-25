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
    /**
     * 重载IModule接口
     * 接口定义详见 ../frontend/include/module.h
     */
    const char *getName() const;
    const char *getGroup() const;
    int open();
    void close();

};

#endif // MODULEHANOI_H
