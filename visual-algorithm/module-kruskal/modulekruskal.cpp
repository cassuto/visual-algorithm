#include "modulekruskal.h"

ModuleKruskal::ModuleKruskal()
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

const char *ModuleKruskal::getName() const
{
    return "最小生成树-Kruskal";
}

const char *ModuleKruskal::getGroup() const
{
    return "图论算法";
}

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
