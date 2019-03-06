######
time.h
######

time.h 头文件提供了与时间日期相关的类型, 函数, 结构体.

类型
====

.. c:type:: time_t

    time_t 是适合存储时间的类型,
    一般为 unsigned int.
    是 :c:func:`time` 的返回值的类型.

    time.h 中声明的许多函数都会接受一个名为 timer 的 time_t 类型参数.

.. c:type:: clock_t

    适合于存储处理器计时的类型.
    一般为 long int.

.. c:type:: struct tm

    一个存储时间日期信息的结构体. 由 :c:func:`localtime` 返回.
    具有以下成员:

    .. c:member:: int tm_year

        年. 注意, 是从 1900 年开始计算的.
        例如, 若得到的值为 119, 则实际上表示 2019 年.

    .. c:member:: int tm_mon

        月. 范围 0~11. 是从 0 开始计算的. 需要注意.

    .. c:member:: int tm_mday

        在某月的第几日. 范围 1~31.
        除了这个成员, 其他都是从 0 开始计算.

    .. c:member:: int tm_wday

        在某一周的第几日. 范围 0~6.

    .. c:member:: int tm_yday

        在某一年的第几日. 范围 0~365.

    .. c:member:: int tm_hour

        二十四小时制. 0~23.

    .. c:member:: int tm_min

        分钟. 0~59.

    .. c:member:: int tm_sec

        秒. 0~59.

    .. c:member:: int tm_isdst

        是否为夏令时. 返回 1 或 0.

    下面两个成员在定义了 :c:macro:`__USE_MISC` 后才会被定义.

    .. c:member:: char* tm_zone

        显示当前时区.

    .. c:member:: long int tm_gmtoff

        与 UTC (太平洋标准时间) 相差的秒数.
        东为正, 西为负.

宏
==

.. c:macro:: long int CLOCKS_PER_SEC

    当前处理器每秒对应的时钟个数.

函数
====

.. c:function:: clock_t clock(void)

    返回从程序开始运行到此时的 CPU 时钟数.
    进程挂起的时间不计算在内.

    算式 返回值 / :c:macro:`CLOCKS_PER_SEC` 将数值单位转化为秒.


.. c:function:: time_t time(time_t* timer)

    返回当前系统时间. (Unix 时间戳).
    如果指针 timer 不是 NULL, 则会将返回值存储在 timer 中.

    :param time_t* timer: time_t 的指针.

.. c:function:: double difftime(time_t time1, time_t time0)

    返回 time1 - time0 的值. 单位为秒.

.. c:function:: struct tm* gmtime(time_t *timer)

    将 timer 解析为 tm 结构体, 使用 UTC 时区(格林威治时间)

.. c:fucntion:: struct tm* localtime(time_t *timer)

    将 timer 解析为 tm 结构体, 使用 本地 时区

.. c:function:: time_t mktime(struct tm *tp)

    将 tm 结构体解析为依据本地时区的 time_t 时间戳.

.. c:function:: size_t strftime(char *str, size_t maxsize, char *fmt, struct tm *tp)

    根据 fmt 将 tm 结构体转化为字符串.

    格式字符串支持的转义符号:

    =========== ======================================= ========
    符号        含义                                    举例
    ----------- --------------------------------------- --------
    %Y          年                                      2019
    %m          月 (01-12)                              03
    %d          日 (01-31)                              07
    %H          时 (00-23)                              00
    %M          分 (00-59)                              07
    %S          秒 (00-59)                              55
    %A          星期名称                                Thursday
    %a          星期缩写                                Thu
    %B          月份名称                                March
    %c          完整的日期时间表示
    %I          12 小时制小时 (01-12)  const struct tm *restrict __tp                 12
    %j          一年的第几天 (01-366)
    %p          AM 或 PM                                AM
    %U          一年的第几周 (00-53) 以第一个星期日开始
    %w          一周的星期几 (0-6)                      4
    %W          一年的第几周 (00-53) 以第一个星期一开始
    %x          日期                                    07/03/19
    %X          时间                                    00:18:22
    %y          年份, 后两位.                           19
    %Z          时区.
    =========== ======================================= ========

    :param char *str: 将生成的字符串存入目标字符数组.
    :param size_t maxsize: 最大可写入的字符数, 一般传入字符数组的长度.
    :param char *fmt: 格式字符串.
    :param struct tm *tp: 存储日期时间信息的 tm 结构体.
    :return: 如果写入的字符数(包括结束符)小于 maxsize,
        则返回去除结束符的写入字符数. 否则返回 0.
    :rtype: size_t

示例
====

.. literalinclude:: _code/time.show.c
    :linenos:
