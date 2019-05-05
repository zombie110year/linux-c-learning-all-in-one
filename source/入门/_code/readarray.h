#ifndef READARRAY_H
#define READARRAY_H

typedef struct {
  int length;
  int *body;
} array_t;

/**
 * 从 path 路径指向的文件中读取数据
 */
int readarray(const char *path, array_t *);
/** 打印数组情况
 *
 */
int printarray(const array_t *array, int counter);

#endif /* READARRAY_H */
