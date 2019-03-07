########
stdarg.h
########

stdarg 提供了可变长参数功能.

类型
====

.. c:type:: va_list

    一个可变长的参数列表.

宏
==

.. c:macro:: va_start(ap, param)

    初始化 :c:type:`va_list` 参数列表.
    可变长参数必须初始化后使用.

    :param ap: 需要初始化的 va_list 变量.
    :param param: 最后一个固定参数.


.. c:macro:: va_arg(ap, type)

    从可变长参数列表 ap 中获取下一个 type 类型的参数.

    如果 ap 中有不同类型的参数,
    且 type 未改变,
    则对应位置的参数会被跳过,
    并且可能访问越界.

    :param ap: 可变长参数列表.
    :param type: 下一个获取的参数值的类型.

.. c:macro:: va_end(ap)

    释放参数列表 ap 占用的内存.

.. c:macro:: va_copy(dest, src)

    将 src 复制到 dest 当中.
    src 的读取状态也会被复制.
    dest 将无法获取已经被 src 提取过的参数.

    :param dest: 复制品
    :param src: 原版
    :type dest: va_list
    :type src: va_list

示例
====

.. literalinclude:: _code/stdarg.show.c
    :linenos:
    :language: c
