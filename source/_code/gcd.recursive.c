#include <stdio.h>

int gcd(int a, int b)
{
    int res = a % b;
    if (res) { // 当 res == 0 时, 表示整除, 但是作为条件表达式, 却表示 False
        return gcd(b, res); // res != 0 时执行
    } else {
        return b;
    }
}

int main(int argc, char* argv[])
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));
    return 0;
}