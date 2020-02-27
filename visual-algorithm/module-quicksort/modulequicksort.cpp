#include "modulequicksort.h"


ModuleQuicksort::ModuleQuicksort()
    : m_data(0)
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

/**
 * @brief 返回算法模块名称
 * @return pointer to string constant value
 */
const char *ModuleQuicksort::getName() const
{
    return "快速排序";
}

/**
 * @brief 返回算法分组名称
 * @return pointer to string constant value
 */
const char *ModuleQuicksort::getGroup() const
{
    return "排序算法";
}

/**
 * @brief 返回模型标识符
 * @return pointer to string constant value
 */
const char *ModuleQuicksort::getModelSymbol() const
{
    return "linearlist";
}

int ModuleQuicksort::open()
{
    return 0;
}

void ModuleQuicksort::close()
{
}

//找基准并进行排序
int Partion(int *arr,int low,int high, IModelLinearList *mdl,IControl *control)
{	int first=low,last=high;
    int temp = arr[low];
    while(low < high)        //当low = high时退出循环,此时的位置为基准位置
    {
       while(low < high && arr[high] > temp)
            high--;

       if(low >= high)
            break;
       else
            arr[low] = arr[high];

       while(low < high && arr[low] < temp)
            low++;

       if(low >= high)
            break;
       else
            arr[high] = arr[low];
   }

   arr[low] = temp;

   //Show(arr,first,last); 			//输出
   // 反馈到前端
   for(int i=1;i<=mdl->getSize();++i) {
        mdl->setElement(i, arr[i]);
   }

   // 等待下一步
   control->waitForNextStep();

   return low;
}

void Quick(int *arr,int start,int end, IModelLinearList *mdl,IControl *control)
{
    int par = Partion(arr,start,end, mdl,control);      //一次找基准
    if(par > start+1)
        Quick(arr,start,par - 1, mdl,control);

    if(par < end - 1)
        Quick(arr,par+1,end, mdl,control);

}
//len为数组的长度
void Quick_Sort(int *arr,int  len, IModelLinearList *mdl,IControl *control)
{
    Quick(arr,1,len, mdl,control);
}

/**
 * @brief 运行算法
 * @param model 模型接口（前端依据getModelSymbol()创建）
 * @param control 控制接口
 * @return status code
 */
int ModuleQuicksort::run(IModel *model, IControl *control)
{
    // 获取前端提供的抽象接口
    IModelLinearList *mdl = static_cast<IModelLinearList *>(model);

    // 从前端读取数据
    int len = mdl->getSize();
    if(m_data) delete [] m_data;
    m_data = new int[len+1];
    for(int i=1;i<=len;++i) {
        m_data[i] = mdl->getElement(i);
    }

    // 运行算法
    Quick_Sort(m_data, len, mdl,control);
    return 0;
}

#if 0
#include<stdio.h>
#define N 10000

void Show(int *arr,int low,int high)
{
    for(int i=low;i<high+1;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int main(){
     int arr[N];
     int n,i;
     scanf("%d",&n);

     for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    Quick_Sort(arr,n);

    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);
}
#endif
