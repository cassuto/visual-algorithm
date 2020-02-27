#include "modulehanoi.h"

ModuleHanoi::ModuleHanoi()
{
}

/**
 * @brief 返回算法模块名称
 * @return pointer to string constant value
 */
const char *ModuleHanoi::getName() const
{
    return "汉诺塔问题";
}

/**
 * @brief 返回算法分组名称
 * @return pointer to string constant value
 */
const char *ModuleHanoi::getGroup() const
{
    return "递归算法";
}

/**
 * @brief 返回模型标识符
 * @return pointer to string constant value
 */
const char *ModuleHanoi::getModelSymbol() const
{
    return "hanoi";
}

int ModuleHanoi::open()
{
    return 0;
}

void ModuleHanoi::close()
{
}

void ModuleHanoi::hanio(int n,char a,char b,char c)
{
    if(n==1){
        // 反馈到前端
        m_model->moveTop(a,c);
        //cout<<a<<"->"<<c<<endl;

        // 等待执行下一步
        m_control->waitForNextStep();
        return ;
    }
    hanio(n-1,a,c,b);
    // 反馈到前端
    m_model->moveTop(a,c);
    //cout<<a<<"->"<<c<<endl;

    // 等待执行下一步
    m_control->waitForNextStep();

    hanio(n-1,b,a,c);
    //count++;
    return ;
}

/**
 * @brief 运行算法
 * @param model 模型接口（前端依据getModelSymbol()创建）
 * @param control 控制接口
 * @return status code
 */
int ModuleHanoi::run(IModel *model, IControl *control)
{
    // 获取前端提供的抽象接口
    m_model = static_cast<IModelHanoi*>(model);
    m_control = control;

    // 从前端获取圆盘数
    int n = m_model->getDisksNum();

    // 初始化塔柱
    m_model->resetPillar();

    // 执行算法
    hanio(n,'A','B','C');
    return 0;
}

#if 0
#include<iostream>
using namespace std;
int count=0;
void hanio(int n,char a,char b,char c);
int main(){
    int n;
    while(cin>>n){
        hanio(n,'A','B','C');
        cout<<count<<endl;
    }
    return 0;
}
void hanio(int n,char a,char b,char c){
    if(n==1){
        cout<<a<<"->"<<c<<endl;
        count++;
        return ;
    }
    hanio(n-1,a,c,b);
    cout<<a<<"->"<<c<<endl;
    hanio(n-1,b,a,c);
    count++;
    return ;
}
#endif

