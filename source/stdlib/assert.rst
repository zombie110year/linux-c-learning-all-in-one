########
assert.h
########

assert.h 头文件中只提供了一个宏函数 :c:func:`assert` 使用.
这个函数将判断传入的表达式的布尔值,
如果判断为假, 则中断程序并输出调试信息.

.. c:function:: assert(expr)

    .. code-block:: c

        #  define assert(expr)							\
        ((void) sizeof ((expr) ? 1 : 0), __extension__ ({			\
            if (expr)								\
                ; /* empty */							\
            else								\
                __assert_fail (#expr, __FILE__, __LINE__, __ASSERT_FUNCTION);	\
            }))
