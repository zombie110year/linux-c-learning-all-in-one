/**
 * 读取数组数据
 *
 * 信息格式::
 *
 *      struct array {
 *          int length;
 *          int *body;
 *      }
 */
#include "readarray.h"
#include <stdio.h>
#include <stdlib.h>

int readarray(const char *path, array_t *array) {
  FILE *src = fopen(path, "rb");
  if (src != NULL) {
    fread(&array->length, sizeof(int), 1, src);
    fread(array->body, sizeof(int), array->length, src);
    return 0;
  } else {
    return -1;
  }
}

/**
 * 打印目标数组的情况
 *
 *  :param array: 将处理的数组
 *  :param counter: 计数器, 记录当前为第几次处理
 */
int printarray(const array_t *array, int counter) {
  printf("%2d: ", counter);
  for (size_t i = 0; i < array->length; i++) {
    printf("%3d, ", *(array->body + i));
  }
  printf("\n");
  return 0;
}
