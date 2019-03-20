######
math.h
######

概览
====

math.h 提供了一系列数学计算相关的函数,
在某些版本的 GCC 中, 需要在链接时指定 libm 才能使用::

    gcc test_math.c -lm

math.h 中的函数传入的参数和返回值都是 :c:type:`double` 类型的.

宏
==

.. c:macro:: HUGE_VAL

    用来表示一个无法用浮点数表示的数,
    可以认为代表 "无穷大"

    当数值超出浮点数范围时, errno 被设为 ERANGE,
    并返回 ``HUGE_VAL`` 或 ``- HUGE_VAL``.

函数
====

三角函数
--------

.. c:function:: double acos(double)

    :return: 反余弦 :math:`\arccos`, 弧度制

.. c:function:: double asin(double)

    :return: 反正弦 :math:`\arcsin`, 弧度制

.. c:function:: double atan(double)

    :return: 反正切 :math:`\arctan`, 弧度制

.. c:function:: double atan2(double y, double x)

    :return: 点 (x, y) 对应的角度, 弧度制

.. c:function:: double sin(double)

    :return: 正弦 :math:`\sin`, 弧度制

.. c:function:: double cos(double)

    :return: 余弦 :math:`\cos`, 弧度制

.. c:function:: double tan(double)

    :return: 正切 :math:`\tan`, 弧度制

双曲函数
--------

.. c:function:: double cosh(double)

    :return: 双曲余弦 :math:`\cosh`

.. c:function:: double sinh(double)

    :return: 双曲正弦 :math:`\sinh`

.. c:function:: double tanh(double)

    :return: 双曲正切 :math:`\tanh`

指数对数
--------

.. c:function:: double exp(double x)

    :return: 指数 :math:`e^x`

.. c:function:: double frexp(double x, int *n)

    分解浮点数 :math:`x = a \times 2^n`

    返回值为 :math:`a`, 将指数存入整数指针 ``n`` 所指的内存.

.. c:function:: double ldexp(double x, int n)

    :return: :math:`x \times 2^n`

.. c:function:: double log(double x)

    :return: 自然对数 :math:`\ln x` (基数为 :math:`e`)

.. c:function:: double log10(double x)

    :return: 常用对数 :math:`\log x`, (基数为 10)

.. c:function:: double pow(double x, double y)

    :return: :math:`x^y`

其他
----

.. c:function:: double sqrt(double x)

    平方根.

    :return: :math:`\sqrt{x}`

.. c:function:: double fmod(double x, double *a)

    分解浮点数为整数与小数部分 :math:`x = a + b`

    -   ``a`` 为整数部分
    -   ``b`` 为小数部分

    小数部分被返回, 整数部分通过指针赋值.

    :return: b

.. c:function:: double modf(double x, double y)

    返回 :math:`x / y` 的余数.

.. c:function:: double ceil(double x)

    向上取整

    .. code-block:: c

        ceil(123.9) == 124.0;
        ceil(123.1) == 124.0;
        ceil(122.9) == 123.0;

.. c:function:: double fabs(double x)

    绝对值

    :return: :math:`|x|`
