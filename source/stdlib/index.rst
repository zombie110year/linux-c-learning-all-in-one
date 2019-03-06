########
C 标准库
########

对于 Linux 系统, 标准库头文件处于目录
``/usr/include`` 之下.
对应的链接库则位于 ``/lib/x86_64-linux-gnu/libc.so.6``.

实际上这是个符号链接, 指向了 ``/lib/x86_64-linux-gnu/libc-2.27.so``.
估计和操作系统的版本有关系.

libc 一般都可执行以显示版本信息::

    $ /lib/x86_64-linux-gnu/libc.so.6

    GNU C Library (Debian GLIBC 2.27-3) stable release version 2.27.
    Copyright (C) 2018 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.
    There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
    PARTICULAR PURPOSE.
    Compiled by GNU CC version 7.3.0.
    libc ABIs: UNIQUE IFUNC
    For bug reporting instructions, please see:
    <http://www.debian.org/Bugs/>.

从路径上可以看出不同的 CPU 架构会影响系统存放库文件的路径.

标准库根据用途不同分成了 15 个不同的头文件.
但他们都会链接到同一个库文件.

assert.h
    提供一个宏, 验证一个表达式的布尔值, 当值为假时输出诊断信息.
ctype.h
    提供了检查变量数值类型的函数.
errno.h
    提供整数变量 errno, 这个变量可由系统自动更改, 或者手动修改.
    它的值对应了不同的错误类型, 可用 man errno 查看.
float.h
    提供了当前平台关于浮点数标准的常量. 只提供信息, 不提供功能.
limits.h
    提供了当前平台关于各类型数值极限的常量. 只提供信息, 不提供功能.
locale.h
    与本地化相关的数据结构与函数. 可用于设定日期格式, 货币符号等等.
math.h
    一系列数学计算函数. 参数与返回值都是 :c:type:`double` 类型.
setjmp.h
    强大的跳转功能. 比 goto 语句更强大也更难用. 不推荐使用.
signal.h
    处理系统信号.
stdarg.h
    提供了一个变长参数列表类型用于函数定义.
stddef.h
    定义的标准扩展类型与宏. 其他头文件大多包含了此头文件.
stdio.h
    与输入输出相关的类型, 函数与宏.
stdlib.h
    通用工具. 与随机数相关的函数与宏也在此头文件中.
string.h
    处理字符串(字符数组).
time.h
    操作日期与时间.

.. toctree::
    :maxdepth: 2
    :glob:

    *
