########
stdlib.h
########

.. highlight:: c

宏
==

.. c:macro:: EXIT_FAILURE

    当程序出错时, 调用 :c:func:`exit` 传入此值::

        #define EXIT_FAILURE 1


.. c:macro:: EXIT_SUCCESS

    当程序顺利运行完成时, 调用 :c:func:`exit` 传入此值::

        #define EXIT_SUCCESS 0

.. c:macro:: RAND_MAX

    :c:func:`rand` 返回的最大值. 资讯型常量, 修改无用.

.. c:macro:: MB_CUR_MAX

    多字符字符集中的最大字符数.

类型
====

.. c:type:: div_t

    .. c:member:: int quot

        除法的商

    .. c:member:: int rem

        除法的余数

.. c:type:: ldiv_t

    .. c:member:: long int quot

        除法的商

    .. c:member:: long int rem

        除法的余数

函数
====

字符转换
--------

.. c:function:: double atof(char *str)

    将 str 指向的字符串解析为浮点数::

        atof("3.1415926") == 3.1415926;
        atof("3.1415926e10") == 3.1415926e10;

    如果无法解析, 则返回 ``0.0``.

.. c:function:: int atoi(char *str)

    将 str 指向的字符串解析为整数::

        atoi("123123") == 123123;

    如果无法解析, 则返回 ``0``.

    如果要解析其他进制表示的整数, 用 :c:func:`strtoi`

.. c:function:: long int atol(char *str)

    解析长整数

.. c:function:: double strtod(char *str, char **endp)

    将一个字符串解析为一个浮点数,
    如果字符串尾部有不可解析的字符, 则会将其地址存入 ``endp``
    如果字符串完全不可解析, 则返回 ``0.0``::

        char **p;
        strtod("1.4e9 people in China", p) == 1.4e9;
        // p -> char *pointer -> " people in China"

.. c:function:: long int strtol(char *str, char **endp, int base)

    将一个字符串解析为一个长整数,
    如果字符串尾部有不可解析的字符, 则会将其地址存入 ``endpointer``
    如果字符串完全不可解析, 则返回 ``0`;
    ``base`` 可接受 0, 2~32 为基底::

        strtol("100", NULL, 10) == 100;
        strtol("100", NULL, 8) == 0100;
        strtol("100", NULL, 16) == 0x100;
        strtol("100", NULL, 2) == 4;
        strtol("100", NULL, 0) == 100; // 十进制

.. c:function:: unsigned long int strtoul(char *str, char **endp, int base)

    类似 :c:func:`strtol`, 不过解析的是无符号长整型.

内存
----

.. c:function:: void *calloc(size_t items, size_t size)

    在堆中分配 ``items * size`` 字节大小的连续内存,
    返回其首地址, 并将内存置零.
    如果失败, 返回 :c:macro:`NULL`

    :param size_t items: 为 items 个元素分配内存
    :param size_t size: 每一个元素的内存大小, 单位字节.

.. c:function:: void *malloc(size_t size)

    在堆中分配 ``size`` 字节大小的连续内存,
    返回其首地址, **不会** 将内存置零.
    如果失败, 返回 :c:macro:`NULL`

    :param size_t size: 将分配的内存大小, 单位字节.

.. c:function:: void *realloc(void *p, size_t new_size)

    将 ``p`` 所指的内存释放, 分配一块新的 ``new_size`` 字节大小的内存,
    并返回新的地址.

.. c:function:: void free(void *p)

    释放 ``p`` 所指向的内存,
    无论它是通过 :c:func:`calloc`, :c:func:`malloc` 还是 :c:func:`realloc` 分配的.

随机数
------

.. c:function:: void srand(unsigned int seed)

    用 ``seed`` 初始化随机数生成器.

.. c:function:: int rand(void)

    返回 0 ~ :c:macro:`RAND_MAX` 之间的随机整数.

操作系统
--------

.. c:function:: void exit(int status_code)

    终止当前进程, 关闭所有相关的文件描述符, 向父进程发送信号.

    :param int status_code: 发送的信号值

.. c:function:: void abort(void)

    终止当前进程, 发送 SIGABRT 信号而不进行善后工作 [#1]_ .

.. [#] https://stackoverflow.com/questions/397075/what-is-the-difference-between-exit-and-abort

.. c:function:: int atexit(void (*func)(void))

    注册一个函数, 让这个函数在程序结束时调用.

    这个函数必须是无返回值, 无参数的函数.

.. c:function:: char *getenv(const char *envname)

    读取一个环境变量.

.. c:function:: int system(char *command)

    在主机的 Shell 环境中运行 command 指令.
    返回系统指令的退出码.

    无法连接输入输出.

搜索与排序
----------

C 标准库提供了快速排序和二分查找.

.. c:function:: void *binsearch(const void *key, void *base, size_t items, size_t size, int (*compare)(const void *, const void *))

    二分查找, 所有的操作都基于指针.

    :param key: 查找目标的指针, 指向一个已定义的对象.
    :param base: 指针, 指向查找区域的起点
    :param size_t items: 查找范围, 元素的数目
    :param size_t size: 查找范围, 元素的尺寸, 单位字节.
    :param compare: 用于对比两个元素大小的函数.
    :return: 指向找到的值的指针.


.. c:function:: void qsort(void *base, size_t items, size_t size, int (*compare)(const void *, const void *))

    快速排序, 所有操作都基于指针.

    :param base: 指针, 排序区域的起点
    :param size_t items: 排序范围, 元素个数
    :param size_t size: 排序范围, 元素尺寸, 单位字节
    :param compare: 对比两个元素大小的函数

关于函数 ``compare``::

    int compare(const void *x, const void *y)
    {
        return (*(int *)x - *(int *)y);
    }

compare 的单调性对排序查找的影响
    如果 x < y, 返回负值, (单调递增) 那么,
    排序后的数组将会从小到大排列, 反之从大到小排列;
    可以查找一个从小到大排序的数组.

绝对值
------

.. c:function:: int abs(int x)

    :return: :math:`|x|`

.. c:function:: long int labs(long int x)

    :return: :math:`|x|`

整数除法
--------

.. c:function:: div_t div(int a, int b)

    整数除法, 返回一个 :c:type:`div_t` 结构体, 储存了商与余数.

    :return: :math:`a \div b`

.. c:function:: ldiv_t div(long int a, long int b)

    整数除法, 返回一个 :c:type:`ldiv_t` 结构体, 储存了商与余数.
    与 :c:func:`div` 不同的是, 此函数处理长整型.

    :return: :math:`a \div b`

宽字符
------

.. todo:: C 语言处理字符串实在繁琐, 日后再提.
