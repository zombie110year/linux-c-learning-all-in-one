#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 可以使用 int array[] 来声明形参是一个 int 数组
// 但是只能声明一维数组, 高维数组只能用多级指针
void displayArray(int array[], int length) {
  for (int i = 0; i < length - 1; ++i) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}

// 也可以使用 int *array, 来声明形参是一个指针
// 效果都一样, 都可以用下标访问元素
void displayArrayPtr(int *array, int length) {
  for (int i = 0; i < length - 1; ++i) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[length - 1]);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL)); // 初始化随机数生成器

  // 声明一个 int 型的指针, 并分配 10 个 int 数据的空间
  int *array = calloc(10, sizeof(int));

  for (int i = 0; i < 10; ++i) {
    // 等价于 *(array + i) = rand() % 100;
    array[i] = rand() % 100; // 可以使用下标用法访问动态数组的元素
  }

  displayArray(array, 10);
  displayArrayPtr(array, 10);

  // 用完后释放
  free(array);
  return 0;
}
