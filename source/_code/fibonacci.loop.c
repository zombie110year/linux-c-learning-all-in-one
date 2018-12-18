#include <stdio.h>
int fibonacci(int n)
{
    int j = 0; // 从 0 开始, 假设为 fib(-1)
    int i = 1; // fib(0) == 1
    int tmp; // 用于交换 i, j 变化前值的临时变量
    /* fib(j) fib(i) fib(n) */
    while (n > 0) {
        tmp = j;
        j = i;
        i += tmp;
        n--;
    }
    /**
     * 最后应当输出 i 还是 j?
     *
     * 当 n 为 0, 则不会循环, 对应的值为 1, 正是 i 的初始值. 由数学归纳法,
     * 应输出 i.
     **/
    return i;
}
/**
 * 预期
 * 0 1
 * 1 1
 * 2 2
 * 3 3
 * 4 5
 * 5 8
 **/
int main(int argc, char* argv[])
{
    int n;
    scanf("%d", &n);
    printf("%d\n", fibonacci(n));
    return 0;
}