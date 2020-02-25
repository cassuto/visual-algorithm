#ifndef ALGORITHMLOADER_H
#define ALGORITHMLOADER_H

#define N_MAX_GROUPS 32

class ModuleLoader
{
public:
    ModuleLoader();

    int getGroupsNum() const;
    const char *getGroupText(int idx) const;

    // Singleton Mode
    static ModuleLoader &instance() {
        if(!m_instance) {
            m_instance = new ModuleLoader;
        }
        return *m_instance;
    }

protected:
    static const int m_ngroups;
    static const char *m_groupText[N_MAX_GROUPS];

private:
    static ModuleLoader *m_instance;
};

#endif // ALGORITHMLOADER_H
