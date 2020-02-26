#include "moduleprim.h"

ModulePrim::ModulePrim()
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

const char *ModulePrim::getName() const
{
    return "最小生成树-Prim";
}

const char *ModulePrim::getGroup() const
{
    return "图论算法";
}

const char *ModulePrim::getModelSymbol() const
{
    return "graph";
}

int ModulePrim::open()
{
    return 0;
}

void ModulePrim::close()
{
}

#if 0
#include<stdio.h>
#include<string.h>
#define INF 9999999
int ans,m,q;
int vis[102],low[102],map[102][102];
void prim()
{
    int i,j,k;
    for(i=2;i<=m;i++)
         low[i]=map[1][i];
         vis[1]=1;
         q=1;
     for(i=2;i<=m;i++)
       {
           int x=1,min=INF;
           for(j=2;j<=m;j++)//寻找最小边
             if(!vis[j]&&low[j]<min)
                {
                    x=j;
                    min=low[j];
                }
             ans+=min;
             if(x==1)
                 break;
                  q++;
             vis[x]=1;//标记顶点
            for(k=2;k<=m;k++)
             if(!vis[k]&&low[k]>map[x][k])
                 low[k]=map[x][k];
       }
}
int main()
{
    int T,i,j,n,x,y,z;
    scanf("%d",&T);
    while(T--)
    {
       memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&m);
        for(i=1;i<=m;i++)
          for(j=1;j<=m;j++)
            if(i!=j)
                 map[i][j]=INF;
            else
                 map[i][j]=0;
        for(i=0;i<n;i++)
         {
             scanf("%d%d%d",&x,&y,&z);
             map[x][y]= map[y][x]=z;
         }
         ans=0;
         prim();
         if(q==m)
                printf("%d\n",ans);
         else
                printf("No solution\n");
    }
    return 0;
}
#endif
