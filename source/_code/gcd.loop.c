#include <stdio.h>
int gcd(int a, int b)
{
    int res, tmp;
    while (res = a % b) { // res = a % b 表达式的值为 最后运算得到的 res 的值.
        a = b;
        b = res;
    } // 当 res == 0 时, 循环中断
    return b;
}
int main(int argc, char const* argv[])
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}
