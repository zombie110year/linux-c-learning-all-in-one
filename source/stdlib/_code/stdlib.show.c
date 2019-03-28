#include <stdio.h>
#include <stdlib.h>

void show_atox(void)
{
    printf("浮点数 %lf\n", atof("1.03123123"));
    printf("浮点数 %lf\n", atof("5.123e9"));

    printf("整数 %d\n", atoi("2121"));
    printf("整数 %x\n", atoi("0x2121"));
}

void show_strtox(void)
{
    char* p;
    printf("浮点数 %lf", strtod("14e8 people in China", &p));
    printf(" 剩下 \"%s\"\n", p);

    printf("整数 %ld", strtol("100 in base 10", &p, 10));
    printf(" 剩下 \"%s\"\n", p);

    printf("整数 %ld", strtol("100 in base 8", &p, 8));
    printf(" 剩下 \"%s\"\n", p);

    printf("整数 %ld", strtol("100 in base 16", &p, 16));
    printf(" 剩下 \"%s\"\n", p);

    printf("整数 %ld", strtol("100 in base 2", &p, 2));
    printf(" 剩下 \"%s\"\n", p);

    printf("整数 %ld", strtol("100 in base 0", &p, 0));
    printf(" 剩下 \"%s\"\n", p);
}

void show_div(void)
{
    div_t output;
    output = div(137, 7);
    printf("商 %d, 余数 %d\n", output.quot, output.rem);
}

void show_wchar(void)
{
    /**
     *  长度: (你好世界)4 + (ascii)12 + (\0)1 = 16 + 1
     */
    wchar_t *test = L"你好世界 Hello World";
    printf("长度: %d", mblen(test, 100));
}

int main(int argc, char* argv[])
{
    show_atox();
    show_strtox();
    show_div();
    show_wchar();
}
