#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t gCOUNT = 1; // 为了和子序列的长度相配合, 这里就设定为 1 吧
const size_t gLENGTH = 5;

/**
 * 打印目标数组的情况
 */
void printArray(int* array, size_t length)
{
    printf("%2I64d: ", gCOUNT); // %I64d 是 size_t 类型的格式符
    for (size_t i = 0; i < length; i++) {
        printf("%3d, ", *(array + i));
    }
    printf("\n");
}

/**
 * 使用插入法将数组排序为从小到大的序列
 */
void insertion_sort(int* array, size_t length)
{
    int key;
    int i;

    for (int j = 1; j < length; j++) {
        printArray(array, length);

        // 选中数组中的一个元素, 从第 1 位开始, 因为如果选 0 开始, 根本没有地方插
        key = array[j];

        for (i = j - 1; i >= 0; i--) { // 这里是 i--, 从右到左遍历, 遍历范围是 0 -> j - 1
            if (array[i] > key) {
                // 因为当前元素比 key 大, 所以把它向后挪, 在前方为较小的 key 腾出位置
                array[i + 1] = array[i];
            } else {
                // 找到了一个 <= key 的, 插在它后面
                break;
            }
        }
        /**
         * 如果是 break 来的
         *     那么说明在中间找到了比 key 小的值, 0<= i < j, i+1 为选中位置的后面
         * 如果是 遍历完了
         *     说明所有 key 前面的值都比它大, 且所有其他元素都向后挪动一位, 因此插在当前位置
         */
        array[i + 1] = key;

        gCOUNT++; // 全局计数器, 计算插入次数
    }
    printArray(array, length);
}

int main(int argc, char const* argv[])
{
    srand(time(NULL));
    size_t length = gLENGTH;
    int array[length];
    for (size_t i = 0; i < length; i++) {
        array[i] = rand() % 100;
    }
    if (length == 5) {
        // 当 LENGTH 设为 5 时打印的表格
        printf("     00   01   02   03   04\n");
        printf(" --  --   --   --   --   --\n");
    }
    insertion_sort(array, length);
    return 0;
}
