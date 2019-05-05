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

#endif /* READARRAY_H */
