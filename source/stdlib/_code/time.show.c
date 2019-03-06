#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#define sleep(ms) Sleep((ms) * 1000)
/**
 * 挂起操作和操作系统有关,
 * 而且 GCC 与 MSVC 分别使用秒和毫秒
 */
#else
#include <unistd.h>
#endif /* _WIN32 */

void show_struct_tm(void)
{
    time_t timer;
    struct tm* date;
    time(&timer);
    date = localtime(&timer);
    printf("year is %d\n", date->tm_year);
    printf("mon is %d\n", date->tm_mon);
    printf("mday is %d\n", date->tm_mday);
    printf("wday is %d\n", date->tm_wday);
    printf("yday is %d\n", date->tm_yday);
    printf("hour is %d\n", date->tm_hour);
    printf("min is %d\n", date->tm_min);
    printf("sec is %d\n", date->tm_sec);
    printf("isdst is %d\n", date->tm_isdst);
    // GLIBC 才包含以下两个成员, 非 C 标准.
    // printf("zone is %s\n", date->tm_zone);
    // printf("gmtoff is %ld\n", date->tm_gmtoff);
    printf("::::%s\n\n", __func__);
}

void show_clock_per_sec(void)
{
    clock_t clocker;
    clocker = clock();
    printf("clock: %ld\n", clocker);
    printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
    printf("::::%s\n\n", __func__);
}

void show_difftime(void)
{
    time_t a, b;
    time(&a);
    sleep(3);
    time(&b);
    printf("TIME1 - TIME2 = %lf\n", difftime(b, a));
    printf("::::%s\n\n", __func__);
}

void show_strtime(void)
{
    time_t timer;
    struct tm *tp;
    char buffer[255] = {'\0'};
    time(&timer);
    tp = localtime(&timer);

    strftime(buffer, 255, "%Y-%m-%d %H:%M:%S", tp);
    printf("%s:::: %s\n", "%Y-%m-%d %H:%M:%S", buffer);
    strftime(buffer, 255, "%c", tp);
    printf("%s:::: %s\n", "%c", buffer);
    strftime(buffer, 255, "%x, %X", tp);
    printf("%s:::: %s\n", "%x, %X", buffer);
    strftime(buffer, 255, "%y", tp);
    printf("%s:::: %s\n", "%y", buffer);
    strftime(buffer, 255, "%I %p", tp);
    printf("%s:::: %s\n", "%I %p", buffer);
    strftime(buffer, 255, "%A, %a, %B", tp);
    printf("%s:::: %s\n", "%A, %a, %B", buffer);
    strftime(buffer, 255, "%Z", tp);
    printf("%s:::: %s\n", "%Z", buffer);

    printf("::::%s\n\n", __func__);
}

int main(int argc, char* argv[])
{
    show_struct_tm();
    show_clock_per_sec();
    show_difftime();
    show_strtime();
    return 0;
}
