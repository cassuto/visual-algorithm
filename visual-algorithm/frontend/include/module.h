#ifndef IMODULE_H
#define IMODULE_H

#include <QtPlugin>

// IModule 接口类
class IModule
{
public:
    IModule() {}
    virtual ~IModule() {}

    /**
     * @brief 获取算法模块名称
     * @return pointer to string constant value
     */
    virtual const char *getName() const=0;
    /**
     * @brief 获取算法分组名称
     * @return group id
     */
    virtual const char *getGroup() const=0;
};

// 声明接口类
Q_DECLARE_INTERFACE(IModule,"algorithm_module/1.0")

#endif // IMODULE_H
