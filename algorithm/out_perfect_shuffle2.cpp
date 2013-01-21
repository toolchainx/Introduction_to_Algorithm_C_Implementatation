/*
算法思路：
原始数组：{a1,a2,a3...an,b1,b2,b3...bn};
目标数组：{a1,b1,a2,b2,a3,b3...an,bn}

可以观察得到目标数组中的索引可以根据原始数组的索引求出来

index : 实际索引（某个元素在实际数组中的索引，每次交换把数组[当前索引]和数组[目标索引]进行交换)
value : 原始索引 (某个元素在原始序列中的索引值，递归时根据这个值来计算它在目标序列中的索引值）
n : 数组大小的一半
count : 执行次数

转换方法为：Ai Bi代表序号
if(Ai < n)
{
    Bi = 2 * Ai ;
}
else 
{
    Bi = 2*(Ai - n) + 1;
}
由这个式子可以推出出现环的情况：
例如： 1 <-> 2  ai = 2ai  
       2 <-> 4  ai = 2ai  
       4 <-> 1  2*(4ai - n) - 1 = ai   <=>  ai = (2n -1)/7 ， (1 + ai*7 )/2 = n。 由于n、ai必须为正整数，所以推出ai只能是奇数。
       更复杂的环的推算也是一样的例如
       1 <-> 2  
       2 <-> 4
       4 <-> 8
       ……
       2^k <-> 1   2*(2^k*ai - n) - 1 = ai   <=>  ai = (2n -1)/(2^k -1) ，ai取1时，可以算出很多种n、k组合，而ai只能为奇数。

       
       时间复杂度：算法的思想是保证每次递归都会至少交换一个元素在对应的位置上，所以移动的最大次数就是数组的大小 - 2，时间复杂度为O(n)。
       空间复杂度：每次交换一个元素只需要一个辅助空间，空间复杂度为O（1）。
       数组的总大小 - 2的说明： 数组除了首尾两个元素外其他的元素都是需要移动的，所以是-2。

       那么为什么出现了第一个环后就会出现第2个环呢（问题等于为什么ai连续取奇数而不会重复呢）?（总长为8除外，它太小了，然后这里可以根据总长的大小推出出现环的次数）

       因为最小数的正整数是1......所以它是最早出现的环，然后结束递归，再次递归时，序号等同于重新由1开始......for中控制的递归次数等于出现环的次数
       
                                你觉得它们的映射关系会重复吗？
*/
void find(int *list,int index,int value,int n,int& count,int& temp)
{
    count++;
    //首尾不需要移动
    if(index == 0 || index == (2*n - 1))
        return;

    //计算对应索引，对应索引同时也是下一步递归的原始索引
    if(value < n)
    {
        value *= 2 ;
    }
    else 
    {
        value = 2*(value - n) + 1;
    }
    //刚好元素已经被移动到目标索引上了
    if(value == index)
        return;
    //交换
    temp = list[value];
    list[value] = list[index];
    list[index] = temp; 
    //递归被交换的元素
    find(list,index,value,n,count,temp);
}

int main()
{
    int list[] = {1,2,3,4,5,6};
    int temp = 0;

    for(int i = 1,count = 0,size = sizeof(list) / sizeof(int); count < size - 2; i+= 2)
    {
        //索引和值相同情况下代表没有修改
        while( list[i] != i)
            i+=2;
        find(list,i,i,size / 2,count,temp);
    }

    return 0;
}
