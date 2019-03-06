#include <stdio.h>

void c_standard_macros(void)
{
    printf("__LINE__ = %d\n", __LINE__);
    printf("__FILE__ = %s\n", __FILE__);
    printf("__DATE__ = %s\n", __DATE__);
    printf("__TIME__ = %s\n", __TIME__);
    printf("__STDC__ = %d\n", __STDC__);
    printf("__func__ = %s\n", __func__);
}

int main(int argc, char *argv[])
{
    c_standard_macros();
    return 0;
}
