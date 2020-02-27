#include "modulequicksort.h"


ModuleQuicksort::ModuleQuicksort()
{
}

/**
 * 重载IModule接口
 * 接口定义详见 ../frontend/include/module.h
 */

const char *ModuleQuicksort::getName() const
{
    return "快速排序";
}

const char *ModuleQuicksort::getGroup() const
{
    return "排序算法";
}

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

#if 0
#include<stdio.h>
#define N 10000

void Show(int *arr,int low,int high)
{
    for(int i=low;i<high+1;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int Partion(int *arr,int low,int high)       //找基准并进行排序
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

   Show(arr,first,last); 			//输出

   return low;
}

void Quick(int *arr,int start,int end)
{
    int par = Partion(arr,start,end);      //一次找基准
    if(par > start+1)
        Quick(arr,start,par - 1);

    if(par < end - 1)
        Quick(arr,par+1,end);

}
void Quick_Sort(int *arr,int  len)      //len为数组的长度
{
    Quick(arr,0,len-1);

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
