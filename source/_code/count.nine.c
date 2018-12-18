/**
 * 循环语句章节的习题 2
 *
 * 编写程序数一下 1 到 100 的所有整数中出现多少次数字 9
 **/
#include <stdio.h>
const int min = 1;
const int max = 100;
const int target = 9;
const int base = 10;
// 到时候把参数一换, 不就能计算任意情况了?
int count9(void)
{
    int count = 0;
    int whole, last; // 整个数, 最后一位, 作为临时变量
    for (int i = min; i <= max; i++) {
        whole = i;
        while (whole) { // 依次核对每一位数
            last = whole % base; // 取个位
            if (last == target) {
                printf("%d ", i);
                count++;
            }
            whole /= base; // 裁剪最后一位
        }
    }
    printf("\n");
    return count;
}
int main(int argc, char const* argv[])
{
    printf("%d", count9());
    return 0;
}
