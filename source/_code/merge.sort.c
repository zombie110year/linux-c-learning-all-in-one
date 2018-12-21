#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// TODO:
const int gLEN = 8;
int gCOUNT = 0;

void mergeSort(int* array, int length);
extern int* array;
/**
 * 打印目标数组的情况
 */
void printArray()
{
    printf("%2d: ", gCOUNT); // %I64d 是 size_t 类型的格式符
    for (size_t i = 0; i < gLEN; i++) {
        printf("%3d, ", *(array + i));
    }
    printf("\n");
}

int main(void)
{
    srand(time(NULL));
    static int array[gLEN];
    for (int i = 0; i < gLEN; i++) {
        array[i] = rand() % 100;
    }
    mergeSort(array, gLEN);
    return 0;
}

/**
 * 归并排序
 */
void mergeSort(int* array, int length)
{
    gCOUNT++;
    printArray();

    int mid = length >> 1; // 将 length 除以二
    int *left, *right;
    left = array;
    right = array + mid;
    // 拆分数组
    if (mid <= 1) {
        mergeSort(left, mid);
        mergeSort(right, length - mid);
    } else {
        for (int i = 0; i < mid; i++) {
            if (left[i] <= right[i]) {
                array[2 * i] = left[i];
                array[2 * i + 1] = right[i];
            } else {
                array[2 * i] = right[i];
                array[2 * i + 1] = left[i];
            }
        }
    }
}
