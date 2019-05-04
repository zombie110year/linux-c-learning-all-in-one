########
stddef.h
########

定义了一些基本的类型与宏, 此头文件常被其他头文件包含.

类型
====

.. c:type:: ptrdiff_t

    指针相减的差值, 有符号整数.

.. c:type:: size_t

    无符号整数, 用来表示一个 "大小", 也是 sizeof 返回的结果.

.. c:type:: wchar_t

    宽字符, 占两个字节. 由于字符编码不统一, 不建议使用.

宏
==

.. c:macro:: NULL

    空指针, 指向 0 地址::

        #define NULL ((void *) 0)


.. c:macro:: offsetof(类型, 成员名)

    返回成员在类型中的字节偏移量.

    例如::

        struct f32array {
            size_t n;
            float *body;
        }

        // offsetof(struct f32array, n) == 0
        // offsetof(struct f32array, body) == 4
