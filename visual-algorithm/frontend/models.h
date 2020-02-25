#ifndef MODELS_H
#define MODELS_H

#include "imodel.h"

/**
 * @brief The ModelFactory class
 * 模型工厂类
 */
class ModelFactory
{
public:
    ModelFactory();

    static ModelFactory &instance() {
        if(!m_instance) {
            m_instance = new ModelFactory();
        }
        return *m_instance;
    }

    /**
     * @brief 根据标识符创建模型类
     * @param symbol 标识符
     * @return pointer to IModel interface class.
     */
    IModel *createModel(const char *symbol);

private:
    static ModelFactory *m_instance;
};

#endif // MODELS_H
