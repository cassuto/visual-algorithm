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

