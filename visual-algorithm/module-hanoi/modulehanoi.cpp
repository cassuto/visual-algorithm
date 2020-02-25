#include "modulehanoi.h"

ModuleHanoi::ModuleHanoi()
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

const char *ModuleHanoi::getName() const
{
    return "汉诺塔问题";
}

const char *ModuleHanoi::getGroup() const
{
    return "递归算法";
}

int ModuleHanoi::open()
{
    return 0;
}

void ModuleHanoi::close()
{
}
