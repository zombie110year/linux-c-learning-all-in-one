#include <stdarg.h>
#include <stdio.h>

/**
 * 虽然第一个参数 count 并不要求为可变参数的数目,
 * 但是读取可变参数的过程中需要这一个参数用于循环.
 *
 * 可以使用多个固定参数, 用省略号 ``...`` 表示接下来的参数数目不定.
 */
int sum(const int count, ...)
{
    va_list args;
    int sum = 0;
    int tmp;
    // 初始化参数列表, 传入第二个参数表示
    // 这个函数的最后一个固定参数.
    va_start(args, count);
    for (int i = 0; i < count; i++){
        // 从参数列表中获取下一个 int 类型的值
        tmp = va_arg(args, int);
        printf("%d, ", tmp);
        sum += tmp;
    }
    va_end(args);
    return sum;
}

double avg(int count, ...)
{
    va_list args, copied;
    double result = 0;
    double result_bak = 0;
    double tmp;
    va_start(args, count);
    // 先用掉一个
    result += va_arg(args, double);
    printf("%lf used, ", result);

    // 复制
    va_copy(copied, args);

    for(double i = 1; i < count; i++){
        tmp = va_arg(args, double);
        printf("%lf, ", tmp);
        result += tmp;
    }
    va_end(args);
    putchar('\n');
    for(double i = 0; i < count; i++){
        tmp = va_arg(copied, double);
        printf("%lf, ", tmp);
        result_bak += tmp;
    }
    va_end(copied);
    putchar('\n');

    return result / count;
}

int main(int argc, char *argv[])
{
    int result;
    // 由于 100.0 处被跳过, 最后访问越界
    result = sum(12, 1, 2, 3, 4, 5, 6, 7, 8, 100.0, 10, 11, 12);
    printf("\n%d\n", result);
    // 正确使用方法
    result = sum(3, 888, 999, 1000);
    printf("\n%d\n", result);

    avg(6, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
    return 0;
}
