/** 
 * 研究如何将迭代程序转换为尾递归程序
 */

// 计算前n项的和
// 递归程序
int recsv_sum(int i)
{
  // 如果利用尾递归实现的话，执行的实际效率会大大提高
  return recsv_sum(i - 1) + i;
}

// 计算前n项的和
// 循环
int iter_sum(int i)
{
  // 变量作为状态来保存
  int count;
  int sum = 0;
  for(count = 0; count <i+1; i++)
    {
      sum += count;
    }    
}

