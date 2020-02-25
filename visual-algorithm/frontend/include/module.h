#ifndef MODULE_H
#define MODULE_H

#define N_MAX_GROUPS 32

class IModule
{
public:
    virtual ModuleLoader()=0;
    virtual ~ModuleLoader() {}
};

#endif // MODULE_H
