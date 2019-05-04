########
stdio.h
########

.. highlight:: c

宏
==

.. c:macro:: EOF

    定义为文件结束符, ``#define -1 EOF``.

.. c:macro:: FOPEN_MAX

    可以同时打开的最大文件数目

.. c:macro:: FILENAME_MAX

    文件名的最大长度

.. c:macro:: SEEK_CUR

    用在 :c:func:`fseek` 函数中, 用于定位文件读写位置.
    此宏表示 "当前读写位置"

.. c:macro:: SEEK_SET

    用在 :c:func:`fseek` 函数中, 用于定位文件读写位置.
    此宏表示 "文件开头"

.. c:macro:: SEEK_END

    用在 :c:func:`fseek` 函数中, 用于定位文件读写位置.
    此宏表示 "文件结尾"

.. c:macro:: BUFSIZ

    当前系统设置的标准文件缓冲区大小. 单位: 字节.

.. c:macro:: _IOFBF

    全缓冲模式, 当缓冲区满时才会发生真实 I/O, 同时清空缓冲区.

.. c:macro:: _IOLBF

    行缓冲模式, 当缓冲区满或者遇到换行符时, 发生真实 I/O, 同时清空缓冲区.

.. c:macro:: _IONBF

    不缓冲模式, 直接进行真实 I/O.

C99 说它们是宏, 让他们高兴
--------------------------

.. c:macro:: stdin

    标准输入流.

.. c:macro:: stdout

    标准输出流.

.. c:macro:: stderr

    标准错误流.

类型
====

.. c:type:: fpos_t

    用于存储文件读写位置的类型. 为整数的别名. 可能是 ``int`` 或 ``long long``.

.. c:type:: FILE

    一个打开的文件类型.

函数
====

标准输入输出
------------

.. c:function:: int getchar(void)

    从 :c:macro:`stdin` 读取一个字节, 作为返回值返回.

    将读写位置正向移动一个字节.

.. note::

    C 语言中没有严谨的 "字符串" 类型. 对于大家常称为字符串的以 ``\0`` 结尾的字符数组,
    它也是以字节为单位进行处理的.
    如果使用了超过 0xff 的编码, 那么一个字符也需要进行多次读取.

.. c:function:: char* gets(char* buffer)

    从 :c:macro:`stdin` 读取一行, 存入到 ``buffer`` 中. 并且将 ``buffer`` 作为返回值返回.
    如果发生错误, 则返回值为 :c:macro:`NULL`, 包含换行符.

    .. warning:: 由于未限制行的长度, 可能存在内存溢出的风险, 不推荐使用.

        应当使用 :c:func:`fgets`, 可以限制一次读取的字节量.

.. c:function:: int putchar(int ch)

    将 ``ch`` 写入到 :c:macro:`stdout` 中. 如果失败, 返回非零值.

.. c:function:: int puts(char* str)

    将 ``str`` 写入到 :c:macro:`stdout` 中. 如果失败, 返回非零值.

.. c:function:: void perror(char* error_name)

    将 ``error_name`` 输出到 :c:macro:`stderr` 中. ``error_name`` 作为输出的错误信息的前缀.
    在前缀后, 会根据全局数组 ``sys_errlist`` 的最后一个值, 附加 ``error_msg``.

    实际上的输出信息是::

        ${error_name}: ${error_msg}

.. c:function:: int scanf(char* fmt, ...)

    从 :c:macro:`stdin` 读取格式化信息. 格式化字符串参考后文的 `格式化输入输出`_

.. c:function:: int printf(char* fmt, ...)

    向 :c:macro:`stdout` 输出格式化信息. 格式化字符串参考后文的 `格式化输入输出`_

读写文件
--------

.. note:: 文件的打开模式

    文件的打开模式使用选项字符串来指定, 会有三种不同角度的选项::

        // 读写方式
        "r"     // 只读, 可读不可泄, 读写指针在文件头部, 如果文件不存在则报错.
        "w"     // 只写, 可写不可读, 读写指针在文件头部, 如果文件不存在则创建, 如果文件已存在则覆盖.
        "a"     // 追加, 可写不可读, 读写指针在文件末尾, 如果文件不存在则会创建.

        // 打开方式
        "t"     // 以文本文件方式打开, 根据系统换行符设置进行换行.
        "b"     // 以二进制模式打开, 不做任何多余的事.

        "+"     // 可更新, 加上此符号, 取消掉读或写的限制, 但其他设置不变.

.. c:function:: FILE* fopen(const char *path, const char *mode)

    以 ``mode`` 方式打开 ``path`` 路径对应的文件. 返回 ``FILE *`` 类型的指针,
    之后的读写等操作通过这个指针进行.

    文件操作完毕后需要 :c:func:`fclose` 来关闭此文件.

.. c:function:: FILE* freopen(const char *path, const char *mode, FILE *stream)

    将 ``stream`` 指针指向一个新打开的文件.

    :param path: 将被打开的新文件
    :param mode: 文件打开模式
    :param stream: 原有的文件指针

.. c:function:: int fclose(FILE *stream)

    关闭 ``stream`` 所指的文件. 会先刷新该文件读写的缓冲区.

.. c:function:: int fgetc(FILE* stream)

    从打开的可读的文本或二进制流 ``stream`` 中读取一个字节, 将其返回并将读写指针后移一个字节.

    如果读取到文件末尾, 那么会得到 :c:macro:`EOF`

.. c:function:: char* fgets(char* buffer, int size, FILE* stream)

    从打开的可读的文本流 ``stream`` 中读取一个字符串, 此字符串以换行符结尾(当然, 最末尾还是 ``\0``),
    将其存入 ``buffer`` 中, ``size`` 通常代表 ``buffer`` 的大小,
    当读取到的字节数达到 ``size - 1`` 后, 读取将中断.

    无论是 ``\r\n`` 还是 ``\n`` 换行, 在程序中都用 ``\n`` 存储换行符.

    -   如果读取成功, 那么读写指针将后移至下一行的行首, 函数将返回读取到的字符数组的首地址(指针).
    -   如果读取失败, 那么函数指针将返回空指针( ``(void*) 0``).
    -   如果读取到文件末尾, 也会返回空指针.

    :param buffer: 字节缓冲区
    :param size: 字节数目

.. c:function:: int fscanf(FILE *stream, const char *format, ...)

    类似于 :c:func:`scanf` 但是将从 ``stream`` 所指定的流中输入.

.. c:function:: size_t fread(void *ptr, size_t size, size_t n, FILE *stream)

    从 ``stream`` 中读取 ``n`` 个 ``size`` 大小的字节块, 存入 ``ptr`` 所指的内存空间中.

.. c:function:: int fputc(int ch, FILE *stream)

    将 ``ch`` 字符输出到 ``stream`` 流.

.. c:function:: int fputs(const char *str, FILE *stream)

    将 ``str`` 字符串输出到 ``stream`` 流. ``\0`` 不会被输出.

.. c:function:: int fprintf(FILE *stream, const char *format, ...)

    类似于 :c:func:`printf` 但是将输出到 ``stream`` 所指定的流中.

.. c:function:: int fwrite(void *ptr, size_t size, size_t n, FILE *stream)

    将指针 ``ptr`` 所指的内存空间中的前 ``n`` 个 ``size`` 大小的字节块输出到 ``stream`` 流中.

.. c:function:: int fflush(FILE *stream)

    刷新 ``stream`` 的输出缓冲区.

文件定位
--------

.. c:function:: int feof(FILE *stream)

    检测 ``stream`` 的读写指针是否已经到达 EOF 位置. 这并不会造成文件读写位置的移动.

.. c:function:: int fgetpos(FILE *stream, fpos_t *pos)

    读取 ``stream`` 的读写位置, 将其存为 :c:type:`fpos_t` 的指针 ``pos`` 所指的值.

.. c:function:: int fsetpos(FILE *stream, const fpos_t *pos)

    将 ``stream`` 的读写位置设置为 ``pos`` 所指的值.

.. c:function:: int fseek(FILE *stream, long offset, int whence)

    将 ``stream`` 的读写位置设置为相对于 ``whence`` 的 ``offset`` 个字节的偏移量.

    whence 的值可选用

    -   ``SEEK_SET``    文件开始
    -   ``SEEK_CUR``    当前位置
    -   ``SEEK_END``    文件末尾

    :param offset: 偏移量
    :param whence: 基准位置

.. c:function:: long ftell(FILE *stream)

    返回 ``stream`` 所指的文件当前读写位置.

.. c:function:: void rewind(FILE *stream)

    将 ``stream`` 的读写位置重设为文件开头.

缓冲设置
--------

.. c:function:: void setbuf(FILE *stream, char *buffer)

    将 ``stream`` 的缓冲区设置为 ``buffer`` 所指的内存区域. 这个区域至少有 :c:macro:`BUFSIZ` 字节大小.

.. c:function:: int setvbuf(FILE *stream, char *buffer, int bufmode, size_t size)

    更详细地设置缓冲区.

    :param bufmode: 缓冲模式, 可选值:

            -   :c:macro:`_IOFBF` : 全缓冲
            -   :c:macro:`_IOLBF` : 行缓冲
            -   :c:macro:`_IONBF` : 不缓冲, size 参数将被忽略

    :param size: 设置缓冲区大小, 单位: 字节.

处理字符串
----------

.. c:function:: int sprintf(const char* str, const char* fmt, ...)

    类似于 :c:func:`printf`, 不过是将格式化的结果存储到 ``str`` 字符串中.

.. c:function:: int sscanf(const char* str, const char* fmt, ...)

    类似 :c:func:`scanf`, 不过是从 ``str`` 字符串中读取格式化信息.

无需打开的文件操作
------------------

.. c:function:: int remove(const char *filepath)

    将 ``filepath`` 路径所指的文件删除

.. c:function:: int rename(const char *old, const char *new)

    将 ``old`` 路径所指的文件重命名(移动)

临时文件
--------

.. c:function:: FILE *tmpfile(void)

    以 ``wb+`` 模式创建一个临时文件, 文件名由操作系统决定.

.. c:function:: char *tmpnam(char *buffer)

    生成一个可用的临时文件路径, 之后可以自行使用 :c:func:`fopen` 创建并打开.

    ``buffer`` 将存储生成的文件名. 如果传入 ``NULL``, 则会在返回值中返回文件路径字符串的首地址.

    如果生成失败, 返回值为 ``NULL``.

va_list 相关
------------

.. c:function:: vprintf(const char *fmt, va_list args)

    将 :c:type:`va_list` 格式的参数格式化输出.

.. c:function:: vfprintf(FILE *stream, const char *fmt, va_list args)

    格式化输出到指定的流.

.. c:function:: vfprintf(char *str, const char *fmt, va_list args)

    格式化输出到指定的字符串.

格式化输入输出
==============

格式化输入时的说明符
--------------------

格式化输入时一个格式化说明符由 ``%[*][宽度][修饰符]<类型符>`` 组成, 类型符是必须的, 其他的可选.

格式化类型符用于限定数据的类型, 决定了字符串的解析方式:

=============== ================================================================
格式化类型符    含义
--------------- ----------------------------------------------------------------
``d``           ``int`` 类型的整数
``c``           ``char`` 类型的字符. 但只能有一个字节长.
``f``           ``float`` 类型的浮点数. 是 ``整数.小数`` 形式的
``e`` ``E``     ``float`` 类型的浮点数. 是 ``有效数字e幂次`` 形式的,
                ``E`` 表示 ``有效数字E幂次``.
``s``           一个 ``\0`` 结尾的 C-style 字符串
``u``           ``unsigned int`` 类型的无符号整数
``o``           ``int`` 类型的八进制整数
``x``           ``int`` 类型的十六进制整数
=============== ================================================================

格式化修饰符修饰了数据的类型:

=============== ================================================================
格式化修饰符    含义
--------------- ----------------------------------------------------------------
``l``           ``long`` 修饰符, 可将整型转为长整型, 单精度浮点数转为双精度
``L``           修饰 ``f``, ``e``, 表示 ``long double`` 类型
``h``           ``short`` 修饰符, 可将整型转为短整型.
=============== ================================================================

宽度限定了读入/输出的字符串的最大宽度: "n" 表示最多读取 n 个字符

``*`` 表示这个说明符仅做占位, 不会将值保存到参数中.

格式化输出时的说明符
--------------------

格式化输出时, 一个格式说明符由 ``%[标志][宽度][.精度][修饰符]<类型符>`` 组成, 类型符是必须的.


格式化类型符用于限定数据的类型, 决定了字符串的解析方式:

=============== ================================================================
格式化类型符    含义
--------------- ----------------------------------------------------------------
``d``           ``int`` 类型的整数
``c``           ``char`` 类型的字符. 但只能有一个字节长.
``f``           ``float`` 类型的浮点数. 是 ``整数.小数`` 形式的
``e`` ``E``     ``float`` 类型的浮点数. 是 ``有效数字e幂次`` 形式的
``g`` ``G``     根据浮点数位数不同, 选择输出宽度最短的 e 或 f 表示法
``s``           一个 ``\0`` 结尾的 C-style 字符串
``u``           ``unsigned int`` 类型的无符号整数
``o``           ``int`` 类型的八进制整数
``x``           ``int`` 类型的十六进制整数
``p``           指针类型, 根据字长的不同, 输出对应位数的十六进制无符号整数
=============== ================================================================

格式化修饰符修饰了数据的类型:

=============== ================================================================
格式化修饰符    含义
--------------- ----------------------------------------------------------------
``l``           ``long`` 修饰符, 可将整型转为长整型, 单精度浮点数转为双精度
``L``           修饰 ``f``, ``e``, 表示 ``long double`` 类型
``h``           ``short`` 修饰符, 可将整型转为短整型.
=============== ================================================================

宽度决定了整个输出字符段的长度, 如果输出长度短于此值, 则用前导空格填充, 如果长于此值, 则输出不会截断.
如果该位置为一个 ``*`` 星号, 则表示在参数列表中增加一个整型参数, 用于指定此说明符的宽度.

精度对于整数, f 型浮点数和 e 型浮点数等的影响不同:

-   整数: 同宽度
-   f, e 型浮点数: 保留的小数位数
-   g 型浮点数: 有效位数
-   s 字符串: 最大的字节数. 如果采用了超过 0xff 的字节编码, 会导致超过限定的字符被截断.
-   如果该位置为一个 ``*`` 星号, 则表示在参数列表中增加一个整型参数, 用于指定此说明符的精度.

标志用于确定该输出字段的样式:

-   ``-`` 指定左对齐, 默认右对齐
-   ``+`` 显示正号, 默认只显示负号
-   `` `` 空格, 当此说明符不输出字符时, 用一个空格代替
-   ``#`` 强制保留一些数据特征:
    -   八进制保留前缀 ``0``
    -   十六进制保留前缀 ``0x``
    -   浮点数保留小数点, 即便小数位全部为 0
-   ``0`` 指定用 0 填充空位, 默认用空格
