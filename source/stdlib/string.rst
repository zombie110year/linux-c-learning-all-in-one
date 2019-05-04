########
string.h
########

string.h 中的功能, 与其说是处理字符串, 不如说是在处理字节数组, 像复制一块内存之类的函数.

如果想要格式化字符串, 需要使用 :doc:`stdio` 中的 :c:func:`sprintf` 函数.

函数
====

内存区域
--------

.. c:function:: void *memchr(const void *str, int ch, size_t size)

    在 str 所指的内存区域前 size 字节中查找第一个出现 ch 字节的位置

    :return: 第一次出现 ch 的地址 (包括此字节)

.. c:function:: int memcmp(const void *a, const void *b, size_t size)

    比较 a, b 的前 size 个字节. 从低位到高位一个字节一个字节地比较,
    当低位出现一个较小的字节时, 判断为小于, 以此类推.

    :return:

        -   -1, 表示 a < b
        -   0, 表示 a == b
        -   1, 表示 a > b

.. c:function:: void *memcpy(void *dest, const void *src, size_t size)

    从 src 到 dest 复制前 size 个字节.

    :param src: 源内存区域
    :param dest: 目标内存区域
    :param size: 将复制的字节数目

.. c:function:: void *memmove(void *dest, const void *src, size_t size)

    从 src 移动 size 个字节到 dest 中. 如果 dest 与 src 在 size 字节内有重叠,
    则此函数将保证 dest 被正确的修改, 而 src 函数可能被更改.
    否则此函数作用与 :c:func:`memcpy` 相同.

.. c:function:: void *memset(void *dest, int ch, size_t size)

    将 dest 的前 size 字节用 ch 填充. 这个函数也常用于设置其他类型的数组.

    :param ch: ch 虽然用 int 类型传入, 但是实际却是当作 unsigned int 类型.

字符串
------

.. c:function:: char *strcat(char *dest, const char *src)

    将 src 追加到 dest 后. dest 是一个 C-style 字符串, 要求能够容纳追加后的字符串.

    :return: dest 的地址

.. c:function:: char *strncat(char *dest, const char *src, size_t n)

    将 src 追加到 dest 后. dest 是一个 C-style 字符串, 要求能够容纳追加后的字符串.
    最多追加 n 个字节.

    :param size_t n: 最大追加的字节数
    :return: dest 的地址

.. c:function:: char *strchr(const char *str, int ch)

    在参数 str 所指的字符串中搜索第一次出现字符 ch 的位置

    :param ch: 虽然以 int 类型传入, 但是实际上用作 unsigned int 类型.
    :return: 返回 ch 出现的地址(包括此字符)

.. c:function:: char *strrchr(const char *str, int ch)

    搜索 str 中最后一次出现字符 ch 的地址.

.. c:function:: size_t strcspn(const char *a, const char *b)

    搜索 a 中第一次出现 b 中字符的位置. 返回的是偏移量, 基准位置是 a 的首地址.

    :return: b 中包含的字符第一次在 a 中出现的地址偏移量

.. c:function:: size_t strspn(const char *a, const char *b)

    在 a 中检索第一个不在 b 中出现的字符的地址偏移量

.. c:function:: char *strpbrk(const char *a, const char *b)

    类似于 :c:func:`strcspn`, 在 a 中检索 b 中的字符, 返回第一次出现的字符的地址.

    :return: b 中包含的字符第一次在 a 中出现的地址

.. c:function:: char *strstr(const char *str, const char *target)

    在 str 中搜索第一次出现 target 字串的地址.

.. c:function:: char *strtok(char *str, const char *delimeter)

    将 str 拆分成子字符串, delimeter 作为分隔符.
    一次调用将会返回一个子串, 当字符串无法再被拆分将会返回 NULL.

    :param delimeter: 分隔符
    :return: 一次调用返回一个子串, 当无法继续拆分时返回 NULL.

.. c:function:: char *strcmp(const char *a, const char *b)

    类似于 :c:func:`memcmp`, 但只针对字符串, 以 ``\0`` 终止.

.. c:function:: char *strcmp(const char *a, const char *b, size_t n)

    类似于 :c:func:`memcmp`, 但只针对字符串, 比较前 n 个字节.

.. c:function:: int strcoll(const char *a, const char *a)

    比较两个字符串的 "大小", 根据 ``LC_COLLATE`` 的设置 [#1]_

.. c:function:: char *strcpy(char *dest, const char *src)

    将 src 复制到 dest

.. c:function:: char *strncpy(char *dest, const char *src, size_t n)

    将 src 复制到 dest, 最多 n 个字节.

.. c:function:: char *strerror(int errno)

    传入 C 错误码, 在内部数组中搜索并返回对应的错误信息.

    :param errno: 常用 errno.h 中的 errno 宏.
    :return: 错误码对应的字符串消息

.. c:function:: size_t strlen(const char *str)

    返回 str 的长度, 单位字节. 以 ``\0`` 结束.

.. c:function:: size_t strxfrm(char *dest, const char *src, size_t n)

    根据 LC_COLLATE 区域设置 [#1]_ , 将 src 转换, 并将结果存入 dest 中.

.. [#1] 参考 https://zh.cppreference.com/w/c/locale/LC_categories, 定义在 locale.h 中.
