#include "modulekruskal.h"

#include <string>
#include <algorithm>
using namespace std;

int father[105];//记录父亲节点，开始都指向自己

int n,m;
struct zhang
{
    int x,y,w;

}t[5009];
bool cmp(const zhang &a,const zhang &b)
{
    return a.w < b.w ;//按权值从小到大排序
}
void kruskal(IModelGraph *mdl, IControl *control)
{
    int find(int x);
    int x,y,i;
    for(i=0;i<m;i++)
    {
        x=find(t[i].x);
        y=find(t[i].y);
        if(x!=y)
         {
             father[x]=y;
             //ans+=t[i].w;

             // 反馈到前端（添加生成树的点和边）
             mdl->addNode(t[i].x);
             mdl->addNode(t[i].y);
             mdl->addEdge(t[i].x, t[i].y, t[i].w);

             // 等待下一步
             control->waitForNextStep();
         }
    }
}
int find(int x)//查找父亲节点
{
    if(father[x]!=x)
      x=find(father[x]);
    return x;
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

/**
 * @brief 运行算法
 * @param model 模型接口（前端依据getModelSymbol()创建）
 * @param control 控制接口
 * @return status code
 */
int ModuleKruskal::run(IModel *model, IControl *control)
{
    int i;
    // 获取前端提供的抽象接口
    IModelGraph *mdl = static_cast<IModelGraph*>(model);

    // 从前端读取结点数、边数
    n = mdl->getNumNodes();
    m = mdl->getNumEdges();

    for(i=1;i<=n;i++)
        father[i]=i;
    for(i=1;i<=m;i++) {
        // 从前端读取一条边
        mdl->getEndpoints(i, &t[i].x, &t[i].y);
        t[i].w = mdl->getWeight(i);
    }

    // 反馈到前端（清除当前图）
    mdl->clear();

    sort(t,t+m,cmp);
    kruskal(mdl, control);

    return 0;
}

ModuleKruskal::ModuleKruskal()
{
}

/**
 * @brief 返回算法模块名称
 * @return pointer to string constant value
 */
const char *ModuleKruskal::getName() const
{
    return "最小生成树-Kruskal";
}

/**
 * @brief 返回算法分组名称
 * @return pointer to string constant value
 */
const char *ModuleKruskal::getGroup() const
{
    return "图论算法";
}

/**
 * @brief 返回模型标识符
 * @return pointer to string constant value
 */
const char *ModuleKruskal::getModelSymbol() const
{
    return "graph";
}

int ModuleKruskal::open()
{
    return 0;
}

void ModuleKruskal::close()
{
}


//////////////////////////////////////////////////////////////////
// 控制台版本
//////////////////////////////////////////////////////////////////
#if 0
#include<stdio.h>
#include<algorithm>
using namespace std;
int n,m,ans;
int father[105];//记录父亲节点，开始都指向自己
struct zhang
{
    int x,y,w;

}t[5009];
bool cmp(const zhang &a,const zhang &b)
{
    return a.w < b.w ;//按权值从小到大排序
}
void kruskal()
{
    int find(int x);
    int x,y,i;
    for(i=0;i<m;i++)
    {
        x=find(t[i].x);
        y=find(t[i].y);
        if(x!=y)
         {
             father[x]=y;
             ans+=t[i].w;
         }
    }
}
int find(int x)//查找父亲节点
{
    if(father[x]!=x)
      x=find(father[x]);
    return x;
}
int main()
{
    int i;
    while(scanf("%d",&n)!=EOF)
    {
        ans=0;
        if(n==0)
             break;
        m=n*(n-1)/2;
        for(i=1;i<=n;i++)
             father[i]=i;
          for(i=0;i<m;i++)
            scanf("%d%d%d",&t[i].x,&t[i].y,&t[i].w);
          sort(t,t+m,cmp);
          kruskal();
          printf("%d\n",ans);
    }
    return 0;
}
#endif
