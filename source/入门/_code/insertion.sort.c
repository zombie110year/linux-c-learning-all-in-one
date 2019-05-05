/**
 * 插入排序
 */
#include "readarray.h" // 引入 readarray 函数, 用于从 10int.array 中获取数据
#include <stdio.h>

// typedef struct {
//     int length;
//     int *body;
// } array_t;

/**
 *  使用插入法将数组排序为从小到大的序列
 *  将序列划分为 "已排序", "未排序" 两个部分
 *
 *  1. 从未排序部分选中一个基准位值
 *  2. 在已排序部分从后向前依次选择, 将元素向后挪, 当找到一个比此位小的值,
 *     则 将 key 插入到此值之后
 *  3. 将已排序部分向后伸展一位
 *
 *  :param array: 要处理的数组, 此结构体指针在整个程序中不会指向其他位置
 *  :param counter: 计数器, 一次调用增加一
 */
void insertion_sort(const array_t *array, int *counter) {
  int key;          // 选择基准位值
  int sorted_i = 0; // 已排序部分的索引
  int j;            // 当前操作位置

  while (sorted_i < array->length && *counter < 1000) { // 防止失败而陷入死循环
    printarray(array, *counter);
    (*(counter))++;
    // 选出未排序部分中的一个元素
    key = array->body[sorted_i];
    // 在已排序部分中进行比较
    for (j = sorted_i; j > 0; --j) {
      if (array->body[j] < key) {
        array->body[j + 1] = key;
        ++sorted_i; // 成功排序一位
        break;
      } else {
        array->body[j] = array->body[j - 1];
      }
    }
    // 如果排到了头部, 则说明 key 在已排序部分最小, 将他插到第一位
    if (j == 0) {
      array->body[j] = key;
      ++sorted_i; // 成功排序一位
    }
  }
}

int main(void) {
  array_t array;
  int counter = 0;
  readarray("10int.array", &array);
  insertion_sort(&array, &counter);
  printarray(&array, -1);
  return 0;
}
