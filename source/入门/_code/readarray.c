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
#include <stdio.h>
#include <stdlib.h>
#include "readarray.h"

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
