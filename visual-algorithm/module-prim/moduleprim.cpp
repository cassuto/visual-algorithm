#include "moduleprim.h"
#include <vector>

#define INF 9999999
int ans,n,m,q;
int vis[102],low[102],map[102][102];
int ex[102],ey[102],ez[102];
std::vector<int> in_mst;
void prim(IModelGraph *mdl, IControl *control)
{
    int i,j,k;
    in_mst.clear();
    for(i=2;i<=m;i++)
         low[i]=map[1][i];
     vis[1]=1;
     q=1;
     in_mst.push_back(1);
     // 反馈到前端（添加生成树的第一个顶点）
     mdl->addNode(1);

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
             in_mst.push_back(x);

             // 反馈到前端（添加连通生成树的顶点和边)
             int mw=INT_MAX, tgt=-1;
             for(int c=0;c<in_mst.size();++c)
               for(int w=1;w<=n;w++) {
                   if((ex[w]==in_mst[c]&&ey[w]==x) || (ex[w]==x&&ey[w]==in_mst[c])) { // 连通点x与pre
                       if(mw > ez[w]) {
                           mw = ez[w];
                           tgt = w;
                       }
                   }
               }
             if(tgt!=-1) {
                mdl->addNode(ex[tgt]);
                mdl->addNode(ey[tgt]);
                mdl->addEdge(ex[tgt], ey[tgt], ez[tgt]);
             }

             // 等待下一步
             control->waitForNextStep();

             if(x==1)
                 break;
                  q++;
             vis[x]=1;//标记顶点
            for(k=2;k<=m;k++)
             if(!vis[k]&&low[k]>map[x][k])
                 low[k]=map[x][k];
       }
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
int ModulePrim::run(IModel *model, IControl *control)
{
    int i,j;
    // 获取前端提供的抽象接口
    IModelGraph *mdl = static_cast<IModelGraph*>(model);

    // 从前端读取结点数、边数
    n = mdl->getNumEdges();
    m = mdl->getNumNodes();

    memset(vis,0,sizeof(vis));
     for(i=1;i<=m;i++)
       for(j=1;j<=m;j++)
         if(i!=j)
              map[i][j]=INF;
         else
              map[i][j]=0;
     for(i=1;i<=n;i++)
      {
          // 从前端读入一条边
          mdl->getEndpoints(i, &ex[i], &ey[i]);
          ez[i] = mdl->getWeight(i);
          //scanf("%d%d%d",&ex[i],&ey[i],&ez[i]);
          map[ex[i]][ey[i]]= map[ey[i]][ex[i]]=ez[i];
      }

      // 反馈到前端（清除当前图）
      mdl->clear();

      ans=0;
      prim(mdl, control);

      // 反馈到前端（算法结果）
      char msg[2048];


      if(q==m)
          snprintf(msg,sizeof msg, "sum{w(G)} = %d", ans);
      else
          snprintf(msg,sizeof msg, "No solution\n");
        mdl->setResult(msg);
      return 0;
}


ModulePrim::ModulePrim()
{
}

/**
 * @brief 返回算法模块名称
 * @return pointer to string constant value
 */
const char *ModulePrim::getName() const
{
    return "最小生成树-Prim";
}

/**
 * @brief 返回算法分组名称
 * @return pointer to string constant value
 */
const char *ModulePrim::getGroup() const
{
    return "图论算法";
}

/**
 * @brief 返回模型标识符
 * @return pointer to string constant value
 */
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

//////////////////////////////////////////////////////////////////
// 控制台版本
//////////////////////////////////////////////////////////////////
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
