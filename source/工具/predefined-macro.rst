############
编译器内置宏
############

C 标准
======

.. c:macro:: __LINE__

    此宏所处的源代码行号.
    在同一个文件中, 在不同行中, 值有所不同.

.. c:macro:: __FILE__

    源代码文件名.

.. c:macro:: __DATE__

    编译日期.

.. c:macro:: __TIME__

    编译时间.

.. c:macro:: __STDC__

    当编译器被要求完全遵守 C 标准,
    禁用编译器扩展时,
    此值设为 1, 否则为 0.

.. c:macro:: __cpludplud

    当编译代码为 C++ 时, 此宏被定义.

.. c:macro:: __func__

    当前所处的函数名.

C99 标准
========

GCC
===

只想要简单查看可以使用命令 ``gcc -dM -E - < /dev/null``.
(其实就是传入空源文件, 查看预处理结果).

或者阅读文档 https://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html

Clang
=====

与 `GCC`_ 类似, ``clang -dM -E - < /dev/null``.

MSVC
====

阅读 MSDN 文档 https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros

确定编译器版本
==============

https://sourceforge.net/p/predef/wiki/Compilers/
总结了各个编译器预定义的与自身版本相关的宏.

确定操作系统
============

对应的操作系统会定义对应的宏.

.. code-block:: c

    __linux__
    _WIN32      // Windows 系统 32 位或 64 位 程序
    _WIN64      // 特指 Windows 系统 64 位 程序
    __APPLE__
