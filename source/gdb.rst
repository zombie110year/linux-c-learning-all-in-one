gdb
###

程序中除了一目了然的Bug之外都需要一定的调试手段来分析到底错在哪。到目前为止我们的调试手段只有一种：根据程序执行时的出错现象假设错误原因，然后在代码中适当的位置插入 ``printf`` ，执行程序并分析打印结果，如果结果和预期的一样，就基本上证明了自己假设的错误原因，就可以动手修正Bug了，如果结果和预期的不一样，就根据结果做进一步的假设和分析。本章我们介绍一种很强大的调试工具 gdb ，可以完全操控程序的运行，使得程序就像你手里的玩具一样，叫它走就走，叫它停就停，并且随时可以查看程序中所有的内部状态，比如各变量的值、传给函数的参数、当前执行的代码行等。掌握了 gdb 的用法之后，调试手段就更加丰富了。但要注意，即使调试手段丰富了，调试的基本思想仍然是 “分析现象->假设错误原因->产生新的现象去验证假设” 这样一个循环，根据现象如何假设错误原因，以及如何设计新的现象去验证假设，这都需要非常严密的分析和思考，如果因为手里有了强大的工具就滥用而忽略了分析过程，往往会治标不治本地修正Bug，导致一个错误现象消失了但Bug仍然存在，甚至是把程序越改越错。本章通过初学者易犯的几个错误实例来讲解如何使用 gdb 调试程序，在每个实例后面总结一部分常用的 gdb 命令。

.. note:: Zombie110year

    现在有许多图形调试工具可以使用, 本人偏爱使用 vscode 中的调试器. TODO:

    但是, 如果你有在控制台字符界面上 debug 的需求, 最好还是学一下 gdb 的用法.

单步执行和跟踪函数调用
======================

看下面的程序：

.. code-block:: c
    :name: 函数调试实例
    :caption: 函数调试实例

    #include <stdio.h>

    int add_range(int low, int high)
    {
        int i, sum;
        for (i = low; i <= high; i++)
            sum = sum + i;
        return sum;
    }

    int main(void)
    {
        int result[100];
        result[0] = add_range(1, 10);
        result[1] = add_range(1, 100);
        printf("result[0]=%d\nresult[1]=%d\n", result[0], result[1]);
        return 0;
    }

``add_range`` 函数从 ``low`` 加到 ``high`` ，在 ``main`` 函数中首先从 ``1`` 加到 ``10`` ，把结果保存下来，然后从 ``1`` 加到 ``100`` ，再把结果保存下来，最后打印的两个结果是：

.. code-block:: c

    result[0]=55
    result[1]=5105

第一个结果正确 [#F20]_ ，第二个结果显然不正确，在小学我们就听说过高斯小时候的故事，从 1 加到 100 应该是 5050 。一段代码，第一次运行结果是对的，第二次运行却不对，这是很常见的一类错误现象，这种情况不应该怀疑代码而应该怀疑数据，因为第一次和第二次运行的都是同一段代码，如果代码是错的，那为什么第一次的结果能对呢？然而第一次和第二次运行时相关的数据却有可能不同，错误的数据会导致错误的结果。在动手调试之前，读者先试试只看代码能不能看出错误原因，只要前面几章学得扎实就应该能看出来。

在编译时要加上 ``-g`` 选项，生成的可执行文件才能用gdb进行源码级调试：

.. code-block:: sh

    $ gcc -g main.c -o main
    $ gdb main
    GNU gdb 6.8-debian
    Copyright (C) 2008 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "i486-linux-gnu"...
    (gdb)

``-g`` 选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证 gdb 能找到源文件。 gdb 提供一个类似 Shell 的命令行环境，上面的 (gdb) 就是提示符，在这个提示符下输入 help可以查看命令的类别：

.. code-block:: sh

    (gdb) help
    List of classes of commands:

    aliases -- Aliases of other commands
    breakpoints -- Making program stop at certain points
    data -- Examining data
    files -- Specifying and examining files
    internals -- Maintenance commands
    obscure -- Obscure features
    running -- Running the program
    stack -- Examining the stack
    status -- Status inquiries
    support -- Support facilities
    tracepoints -- Tracing of program execution without stopping the program
    user-defined -- User-defined commands

    Type "help" followed by a class name for a list of commands in that class.
    Type "help all" for the list of all commands.
    Type "help" followed by command name for full documentation.
    Type "apropos word" to search for commands related to "word".
    Command name abbreviations are allowed if unambiguous.

也可以进一步查看某一类别中有哪些命令，例如查看 ``files`` 类别下有哪些命令可用：

.. code-block:: none

    (gdb) help files
    Specifying and examining files.

    List of commands:

    add-shared-symbol-files -- Load the symbols from shared objects in the dynamic linker's link map
    add-symbol-file -- Load symbols from FILE
    add-symbol-file-from-memory -- Load the symbols out of memory from a dynamically loaded object file
    cd -- Set working directory to DIR for debugger and program being debugged
    core-file -- Use FILE as core dump for examining memory and registers
    directory -- Add directory DIR to beginning of search path for source files
    edit -- Edit specified file or function
    exec-file -- Use FILE as program for getting contents of pure memory
    file -- Use FILE as program to be debugged
    forward-search -- Search for regular expression (see regex(3)) from last line listed
    generate-core-file -- Save a core file with the current state of the debugged process
    list -- List specified function or line
    ...

现在试试用 ``list`` 命令从第一行开始列出源代码：

.. code-block:: none

    (gdb) list 1
    1	#include <stdio.h>
    2
    3	int add_range(int low, int high)
    4	{
    5		int i, sum;
    6		for (i = low; i <= high; i++)
    7			sum = sum + i;
    8		return sum;
    9	}
    10

一次只列10行，如果要从第11行开始继续列源代码可以输入

.. code-block:: none

    (gdb) list

也可以什么都不输直接敲回车，gdb 提供了一个很方便的功能，在提示符下直接敲回车表示重复上一条命令。

.. code-block:: none

    (gdb) （直接回车）
    11	int main(void)
    12	{
    13		int result[100];
    14		result[0] = add_range(1, 10);
    15		result[1] = add_range(1, 100);
    16		printf("result[0]=%d\nresult[1]=%d\n", result[0], result[1]);
    17		return 0;
    18

gdb 的很多常用命令有简写形式，例如 list 命令可以写成 l，要列一个函数的源代码也可以用函数名做参数：

.. code-block:: none

    (gdb) l add_range
    1	#include <stdio.h>
    2
    3	int add_range(int low, int high)
    4	{
    5		int i, sum;
    6		for (i = low; i <= high; i++)
    7			sum = sum + i;
    8		return sum;
    9	}
    10

现在退出gdb的环境::

    (gdb) quit

我们做一个实验，把源代码改名或移到别处再用 gdb 调试，这样就列不出源代码了：

.. code-block:: sh

    $ mv main.c mian.c
    $ gdb main
    ...
    (gdb) l
    5	main.c: No such file or directory.
        in main.c

可见 gcc 的 ``-g`` 选项并不是把源代码嵌入到可执行文件中的，在调试时也需要源文件。现在把源代码恢复原样，我们继续调试。首先用 start 命令开始执行程序：

.. code-block:: sh

    $ gdb main
    ...
    (gdb) start
    Breakpoint 1 at 0x80483ad: file main.c, line 14.
    Starting program: /home/akaedu/main
    main () at main.c:14
    14		result[0] = add_range(1, 10);
    (gdb)

gdb停在main函数中变量定义之后的第一条语句处等待我们发命令，gdb列出的这条语句是即将执行的下一条语句。我们可以用 next 命令（简写为n）控制这些语句一条一条地执行：

.. code-block:: none

    (gdb) n
    15		result[1] = add_range(1, 100);
    (gdb) （直接回车）
    16		printf("result[0]=%d\nresult[1]=%d\n", result[0], result[1]);
    (gdb) （直接回车）
    result[0]=55
    result[1]=5105
    17		return 0;

用 ``n`` 命令依次执行两行赋值语句和一行打印语句，在执行打印语句时结果立刻打出来了，然后停在 ``return`` 语句之前等待我们发命令。虽然我们完全控制了程序的执行，但仍然看不出哪里错了，因为错误不在 ``main`` 函数中而在 ``add_range`` 函数中，现在用 ``start`` 命令重新来过，这次用 ``step`` 命令（简写为 ``s`` ）钻进 ``add_range`` 函数中去跟踪执行：

.. code-block:: none

    (gdb) start
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y

    Breakpoint 2 at 0x80483ad: file main.c, line 14.
    Starting program: /home/akaedu/main
    main () at main.c:14
    14		result[0] = add_range(1, 10);
    (gdb) s
    add_range (low=1, high=10) at main.c:6
    6		for (i = low; i <= high; i++)

这次停在了 ``add_range`` 函数中变量定义之后的第一条语句处。在函数中有几种查看状态的办法， ``backtrace`` 命令（简写为 ``bt`` ）可以查看函数调用的栈帧：

.. code-block:: none

    (gdb) bt
    #0  add_range (low=1, high=10) at main.c:6
    #1  0x080483c1 in main () at main.c:14

可见当前的 ``add_range`` 函数是被 ``main`` 函数调用的， ``main`` 传进来的参数是 ``low=1`` , ``high=10`` 。 ``main`` 函数的栈帧编号为 1， ``add_range`` 的栈帧编号为 0。现在可以用 ``info`` 命令（简写为 i ）查看 ``add_range`` 函数局部变量的值：

.. code-block:: none

    (gdb) i locals
    i = 0
    sum = 0

如果想查看 ``main`` 函数当前局部变量的值也可以做到，先用 ``frame`` 命令（简写为f）选择1号栈帧然后再查看局部变量：

.. code-block:: none

    (gdb) f 1
    #1  0x080483c1 in main () at main.c:14
    14		result[0] = add_range(1, 10);
    (gdb) i locals
    result = {0, 0, 0, 0, 0, 0, 134513196, 225011984, -1208685768, -1081160480,
    ...
    -1208623680}

注意到 ``result`` 数组中有很多元素具有杂乱无章的值，我们知道未经初始化的局部变量具有不确定的值。到目前为止一切正常。用 ``s`` 或 ``n`` 往下走几步，然后用 ``print`` 命令（简写为 ``p`` ）打印出变量 ``sum`` 的值：

.. code-block:: none

    (gdb) s
    7 sum = sum + i;
    (gdb) （直接回车）
    6 for (i = low; i <= high; i++)
    (gdb) （直接回车）
    7 sum = sum + i;
    (gdb) （直接回车）
    6 for (i = low; i <= high; i++)
    (gdb) p sum
    $1 = 3

第一次循环 ``i`` 是 ``1`` ，第二次循环 ``i`` 是 2，加起来是 ``3`` ，没错。这里的 ``$1`` 表示gdb保存着这些中间结果， ``$`` 后面的编号会自动增长，在命令中可以用 ``$1`` 、 ``$2`` 、 ``$3`` 等编号代替相应的值。由于我们本来就知道第一次调用的结果是正确的，再往下跟也没意义了，可以用 ``finish`` 命令让程序一直运行到从当前函数返回为止：

.. code-block:: none

    (gdb) finish
    Run till exit from #0  add_range (low=1, high=10) at main.c:6
    0x080483c1 in main () at main.c:14
    14		result[0] = add_range(1, 10);
    Value returned is $2 = 55

返回值是 ``55`` ，当前正准备执行赋值操作，用 ``s`` 命令赋值，然后查看 ``result`` 数组：

.. code-block:: none

    (gdb) s
    15		result[1] = add_range(1, 100);
    (gdb) p result
    $3 = {55, 0, 0, 0, 0, 0, 134513196, 225011984, -1208685768, -1081160480,
    ...
    -1208623680}

第一个值 55 确实赋给了 ``result`` 数组的第 0 个元素。下面用 ``s`` 命令进入第二次 ``add_range`` 调用，进入之后首先查看参数和局部变量：

.. code-block:: none

    (gdb) s
    add_range (low=1, high=100) at main.c:6
    6		for (i = low; i <= high; i++)
    (gdb) bt
    #0  add_range (low=1, high=100) at main.c:6
    #1  0x080483db in main () at main.c:15
    (gdb) i locals
    i = 11
    sum = 55

由于局部变量 ``i`` 和 ``sum`` 没初始化，所以具有不确定的值，又由于两次调用是挨着的， ``i`` 和 ``sum`` 正好取了上次调用时的值，原来这跟 :ref:`验证局部变量存储空间的分配和释放` 是一样的道理，只不过我这次举的例子设法让局部变量 ``sum`` 在第一次调用时初值为 0 了。 ``i`` 的初值不是 0 倒没关系，在 for 循环中会赋值为 0 的，但 ``sum`` 如果初值不是 0 ，累加得到的结果就错了。好了，我们已经找到错误原因，可以退出 gdb 修改源代码了。如果我们不想浪费这次调试机会，可以在 gdb 中马上把 sum 的初值改为 0 继续运行，看看这一处改了之后还有没有别的Bug：

.. code-block:: none

    (gdb) set var sum=0
    (gdb) finish
    Run till exit from #0  add_range (low=1, high=100) at main.c:6
    0x080483db in main () at main.c:15
    15		result[1] = add_range(1, 100);
    Value returned is $4 = 5050
    (gdb) n
    16		printf("result[0]=%d\nresult[1]=%d\n", result[0], result[1]);
    (gdb) （直接回车）
    result[0]=55
    result[1]=5050
    17		return 0;

这样结果就对了。修改变量的值除了用 ``set`` 命令之外也可以用 ``print`` 命令，因为 ``print`` 命令后面跟的是表达式，而我们知道赋值和函数调用也都是表达式，所以也可以用 ``print`` 命令修改变量的值或者调用函数：

.. code-block:: none

    (gdb) p result[2]=33
    $5 = 33
    (gdb) p printf("result[2]=%d\n", result[2])
    result[2]=33
    $6 = 13

我们讲过， ``printf`` 的返回值表示实际打印的字符数，所以 ``$6`` 的结果是 13。总结一下本节用到的 gdb 命令：

.. table:: gdb基本命令1
    :name: gdb基本命令1

    ======================= ========================================================
    命令                    描述
    ----------------------- --------------------------------------------------------
    backtrace（或bt）       查看各级函数调用及参数
    finish                  连续运行到当前函数返回为止，然后停下来等待命令
    frame（或f） 帧编号     选择栈帧
    info（或i） locals      查看当前栈帧局部变量的值
    list（或l）             列出源代码，接着上次的位置往下列，每次列10行
    list 行号               列出从第几行开始的源代码
    list 函数名             列出某个函数的源代码
    next（或n）             执行下一行语句
    print（或p）            打印表达式的值，通过表达式可以修改变量的值或者调用函数
    quit（或q）             退出gdb调试环境
    set var                 修改变量的值
    start                   开始执行程序，停在main函数第一行语句前面等待命令
    step（或s）             执行下一行语句，如果有函数调用则进入到函数中
    ======================= ========================================================

.. 显示不够宽

习题
----

1、用 gdb 一步一步跟踪 :ref:`递归` 讲的 ``factorial`` 函数，对照着 :ref:`factorial(3)的调用过程` 查看各层栈帧的变化情况，练习本节所学的各种 gdb 命令。

.. [#F20] 这么说不够准确，在有些平台和操作系统上第一个结果也未必正确，如果在你机器上运行第一个结果也不正确，首先检查一下程序有没有抄错，如果没抄错那就没关系了，顺着我的讲解往下看就好了，结果是多少都无关紧要。

断点
====

看以下程序：


.. code-block:: c
    :name: 断点调试实例

    #include <stdio.h>

    int main(void)
    {
        int sum = 0, i = 0;
        char input[5];

        while (1) {
            scanf("%s", input);
            for (i = 0; input[i] != '\0'; i++)
                sum = sum*10 + input[i] - '0';
            printf("input=%d\n", sum);
        }
        return 0;
    }

这个程序的作用是：首先从键盘读入一串数字存到字符数组 ``input`` 中，然后转换成整型存到 ``sum`` 中，然后打印出来，一直这样循环下去。 ``scanf("%s", input);`` 这个调用的功能是等待用户输入一个字符串并回车， ``scanf`` 把其中第一段非空白（非空格、Tab、换行）的字符串保存到 ``input`` 数组中，并自动在末尾添加 ``'\0'`` 。接下来的循环从左到右扫描字符串并把每个数字累加到结果中，例如输入是 ``"2345"`` ，则循环累加的过程是 ``(((0*10+2)*10+3)*10+4)*10+5=2345`` 。注意字符型的 ``'2'`` 要减去 ``'0'`` 的 ASCII 码才能转换成整数值 ``2`` 。下面编译运行程序看看有什么问题

.. code-block:: none

    $ gcc main.c -g -o main
    $ ./main
    123
    input=123
    234
    input=123234
    （Ctrl-C退出程序）
    $

又是这种现象，第一次是对的，第二次就不对。可是这个程序我们并没有忘了赋初值，不仅 ``sum`` 赋了初值，连不必赋初值的 ``i`` 都赋了初值。读者先试试只看代码能不能看出错误原因。下面来调试：

.. code-block:: none

    $ gdb main
    ...
    (gdb) start
    Breakpoint 1 at 0x80483b5: file main.c, line 5.
    Starting program: /home/akaedu/main
    main () at main.c:5
    5		int sum = 0, i = 0;

有了上一次的经验， ``sum`` 被列为重点怀疑对象，我们可以用 ``display`` 命令使得每次停下来的时候都显示当前 ``sum`` 的值，然后继续往下走：

.. code-block:: none

    (gdb) display sum
    1: sum = -1208103488
    (gdb) n
    9			scanf("%s", input);
    1: sum = 0
    (gdb)
    123
    10			for (i = 0; input[i] != '\0'; i++)
    1: sum = 0

``undisplay`` 命令可以取消跟踪显示，变量 ``sum`` 的编号是 1 ，可以用 ``undisplay 1`` 命令取消它的跟踪显示。这个循环应该没有问题，因为上面第一次输入时打印的结果是正确的。如果不想一步一步走这个循环，可以用 ``break`` 命令（简写为 b ）在第 9 行设一个断点（ ``Breakpoint`` ） ：

.. code-block:: none

    (gdb) l
    5		int sum = 0, i;
    6		char input[5];
    7
    8		while (1) {
    9			scanf("%s", input);
    10			for (i = 0; input[i] != '\0'; i++)
    11				sum = sum*10 + input[i] - '0';
    12			printf("input=%d\n", sum);
    13		}
    14		return 0;
    (gdb) b 9
    Breakpoint 2 at 0x80483bc: file main.c, line 9.

``break`` 命令的参数也可以是函数名，表示在某个函数开头设断点。现在用 ``continue`` 命令（简写为 ``c`` ）连续运行而非单步运行，程序到达断点会自动停下来，这样就可以停在下一次循环的开头：

.. code-block:: none

    (gdb) c
    Continuing.
    input=123

    Breakpoint 2, main () at main.c:9
    9			scanf("%s", input);
    1: sum = 123

然后输入新的字符串准备转换：

.. code-block:: none

    (gdb) n
    234
    10			for (i = 0; input[i] != '\0'; i++)
    1: sum = 123

问题暴露出来了，新的转换应该再次从 0 开始累加，而 ``sum`` 现在已经是 123 了，原因在于新的循环没有把 ``sum`` 归零。可见断点有助于快速跳过没有问题的代码，然后在有问题的代码上慢慢走慢慢分析，“断点加单步”是使用调试器的基本方法。至于应该在哪里设置断点，怎么知道哪些代码可以跳过而哪些代码要慢慢走，也要通过对错误现象的分析和假设来确定，以前我们用 ``printf`` 打印中间结果时也要分析应该在哪里插入 ``printf`` ，打印哪些中间结果，调试的基本思路是一样的。一次调试可以设置多个断点，用 ``info`` 命令可以查看已经设置的断点：

.. code-block:: none

    (gdb) b 12
    Breakpoint 3 at 0x8048411: file main.c, line 12.
    (gdb) i breakpoints
    Num     Type           Disp Enb Address    What
    2       breakpoint     keep y   0x080483c3 in main at main.c:9
        breakpoint already hit 1 time
    3       breakpoint     keep y   0x08048411 in main at main.c:12

每个断点都有一个编号，可以用编号指定删除某个断点：

.. code-block:: none

    (gdb) delete breakpoints 2
    (gdb) i breakpoints
    Num     Type           Disp Enb Address    What
    3       breakpoint     keep y   0x08048411 in main at main.c:12

有时候一个断点暂时不用可以禁用掉而不必删除，这样以后想用的时候可以直接启用，而不必重新从代码里找应该在哪一行设断点：

.. code-block:: none

    (gdb) disable breakpoints 3
    (gdb) i breakpoints
    Num     Type           Disp Enb Address    What
    3       breakpoint     keep n   0x08048411 in main at main.c:12
    (gdb) enable 3
    (gdb) i breakpoints
    Num     Type           Disp Enb Address    What
    3       breakpoint     keep y   0x08048411 in main at main.c:12
    (gdb) delete breakpoints
    Delete all breakpoints? (y or n) y
    (gdb) i breakpoints
    No breakpoints or watchpoints.

gdb 的断点功能非常灵活，还可以设置断点在满足某个条件时才激活，例如我们仍然在循环开头设置断点，但是仅当 ``sum`` 不等于 0 时才中断，然后用 ``run`` 命令（简写为 ``r`` ）重新从程序开头连续运行：

.. code-block:: none

    (gdb) break 9 if sum != 0
    Breakpoint 5 at 0x80483c3: file main.c, line 9.
    (gdb) i breakpoints
    Num     Type           Disp Enb Address    What
    5       breakpoint     keep y   0x080483c3 in main at main.c:9
        stop only if sum != 0
    (gdb) r
    The program being debugged has been started already.
    Start it from the beginning? (y or n) y
    Starting program: /home/akaedu/main
    123
    input=123

    Breakpoint 5, main () at main.c:9
    9			scanf("%s", input);
    1: sum = 123

结果是第一次执行 ``scanf`` 之前没有中断，第二次却中断了。总结一下本节用到的 gdb 命令：

.. table:: gdb基本命令2
    :name: gdb基本命令2

    ======================= ============================================
    命令                    描述
    ----------------------- --------------------------------------------
    break（或b） 行号       在某一行设置断点
    break 函数名            在某个函数开头设置断点
    break ... if ...        设置条件断点
    continue（或c）         从当前位置开始连续运行程序
    delete breakpoints      断点号 	删除断点
    display 变量名          跟踪查看某个变量，每次停下来都显示它的值
    disable breakpoints     断点号 	禁用断点
    enable 断点号           启用断点
    info（或i） breakpoints 查看当前设置了哪些断点
    run（或r）              从头开始连续运行程序
    undisplay 跟踪显示号    取消跟踪显示
    ======================= ============================================

习题
----

1、看下面的程序：

.. code-block:: c

    #include <stdio.h>

    int main(void)
    {
        int i;
        char str[6] = "hello";
        char reverse_str[6] = "";

        printf("%s\n", str);
        for (i = 0; i < 5; i++)
            reverse_str[5-i] = str[i];
        printf("%s\n", reverse_str);
        return 0;
    }

首先用字符串 ``"hello"`` 初始化一个字符数组 ``str`` （算上 ``'\0'`` 共 6 个字符）。然后用空字符串 ``""`` 初始化一个同样长的字符数组 ``reverse_str`` ，相当于所有元素用 ``'\0'`` 初始化。然后打印 ``str`` ，把 ``str`` 倒序存入 ``reverse_str`` ，再打印 ``reverse_str`` 。然而结果并不正确：

.. code-block:: none

    $ ./main
    hello

我们本来希望 ``reverse_str`` 打印出来是 ``olleh`` ，结果什么都没有。重点怀疑对象肯定是循环，那么简单验算一下， ``i=0`` 时， ``reverse_str[5]=str[0]`` ，也就是 ``'h'`` ， ``i=1`` 时， ``reverse_str[4]=str[1]`` ，也就是 ``'e'`` ，依此类推， ``i=0,1,2,3,4`` ，共 5 次循环，正好把 ``h``, ``e`` , ``l`` , ``l`` , ``o`` 五个字母给倒过来了，哪里不对了？用 gdb 跟踪循环，找出错误原因并改正。

观察点
======

接着上一节的步骤，经过调试我们知道，虽然 ``sum`` 已经赋了初值 0 ，但仍需要在 while (1) 循环的开头加上 ``sum = 0;`` ：

.. code-block:: c
    :name: 观察点调试实例

    #include <stdio.h>

    int main(void)
    {
        int sum = 0, i = 0;
        char input[5];

        while (1) {
            sum = 0;
            scanf("%s", input);
            for (i = 0; input[i] != '\0'; i++)
                sum = sum*10 + input[i] - '0';
            printf("input=%d\n", sum);
        }
        return 0;
    }

使用 ``scanf`` 函数是非常凶险的，即使修正了这个 Bug 也还存在很多问题。如果输入的字符串超长了会怎么样？我们知道数组访问越界是不会检查的，所以 ``scanf`` 会写出界。现象是这样的：

.. code-block:: none

    $ ./main
    123
    input=123
    67
    input=67
    12345
    input=123407

下面用调试器看看最后这个诡异的结果是怎么出来的 [#F21]_。

.. code-block:: none

    $ gdb main
    ...
    (gdb) start
    Breakpoint 1 at 0x80483b5: file main.c, line 5.
    Starting program: /home/akaedu/main
    main () at main.c:5
    5		int sum = 0, i = 0;
    (gdb) n
    9			sum = 0;
    (gdb) （直接回车）
    10			scanf("%s", input);
    (gdb) （直接回车）
    12345
    11			for (i = 0; input[i] != '\0'; i++)
    (gdb) p input
    $1 = "12345"

``input`` 数组只有 5 个元素，写出界的是 ``scanf`` 自动添的 ``'\0'`` ，用 ``x`` 命令看会更清楚一些：

.. code-block:: none

    (gdb) x/7b input
    0xbfb8f0a7:	0x31	0x32	0x33	0x34	0x35	0x00	0x00

``x`` 命令打印指定存储单元的内容。 ``7b`` 是打印格式， b 表示每个字节一组， 7 表示打印 7 组 [#F22]_ ，从 ``input`` 数组的第一个字节开始连续打印 7 个字节。前 5 个字节是 ``input`` 数组的存储单元，打印的正是十六进制 ASCII 码的 ``'1'`` 到 ``'5'`` ，第 6 个字节是写出界的 ``'\0'`` 。根据运行结果，前 4 个字符转成数字都没错，第 5 个错了，也就是 i 从 0 到 3 的循环都没错，我们设一个条件断点从 ``i`` 等于 4 开始单步调试：

.. code-block:: none

    (gdb) l
    6		char input[5];
    7
    8		while (1) {
    9			sum = 0;
    10			scanf("%s", input);
    11			for (i = 0; input[i] != '\0'; i++)
    12				sum = sum*10 + input[i] - '0';
    13			printf("input=%d\n", sum);
    14		}
    15		return 0;
    (gdb) b 12 if i == 4
    Breakpoint 2 at 0x80483e6: file main.c, line 12.
    (gdb) c
    Continuing.

    Breakpoint 2, main () at main.c:12
    12				sum = sum*10 + input[i] - '0';
    (gdb) p sum
    $2 = 1234

现在 ``sum`` 是 1234 没错，根据运行结果是 123407 我们知道即将进行的这步计算肯定要出错，算出来应该是 12340 ，那就是说 ``input[4]`` 肯定不是'5'了，事实证明这个推理是不严谨的：

.. code-block:: none

    (gdb) x/7b input
    0xbfb8f0a7:	0x31	0x32	0x33	0x34	0x35	0x04	0x00

``input[4]`` 的确是 ``0x35`` ，产生 ``123407`` 还有另外一种可能，就是在下一次循环中 ``123450`` 不是加上而是减去一个数得到 ``123407`` 。可现在不是到字符串末尾了吗？怎么会有下一次循环呢？注意到循环控制条件是 ``input[i] != '\0'`` ，而本来应该是 ``0x00`` 的位置现在莫名其妙地变成了 ``0x04`` ，因此循环不会结束。继续单步：

.. code-block:: none

    (gdb) n
    11			for (i = 0; input[i] != '\0'; i++)
    (gdb) p sum
    $3 = 12345
    (gdb) n
    12				sum = sum*10 + input[i] - '0';
    (gdb) x/7b input
    0xbfb8f0a7:	0x31	0x32	0x33	0x34	0x35	0x05	0x00

进入下一次循环，原来的 ``0x04`` 又莫名其妙地变成了 ``0x05`` ，这是怎么回事？这个暂时解释不了，但 123407 这个结果可以解释了，是 ``12345*10 + 0x05 - 0x30`` 得到的，虽然多循环了一次，但下次一定会退出循环了，因为 0x05 的后面是 ``'\0'`` 。

``input[4]`` 后面那个字节到底是什么时候变的？可以用观察点 （Watchpoint） 来跟踪。我们知道断点是当程序执行到某一代码行时中断，而观察点是当程序访问某个存储单元时中断，如果我们不知道某个存储单元是在哪里被改动的，这时候观察点尤其有用。下面删除原来设的断点，从头执行程序，重复上次的输入，用 ``watch`` 命令设置观察点，跟踪 ``input[4]`` 后面那个字节（可以用 ``input[5]`` 表示，虽然这是访问越界）：

.. code-block:: none

    (gdb) delete breakpoints Delete all breakpoints? (y or n) y
    (gdb) start Breakpoint 1 at 0x80483b5: file main.c, line 5.
    Starting program: /home/akaedu/main main () at main.c:5
    5 int sum = 0, i = 0;
    (gdb) n 9 sum = 0;
    (gdb) （直接回车）
    10 scanf("%s", input);
    (gdb) （直接回车） 12345
    11 for (i = 0; input[i] != '\0'; i++)
    (gdb) watch input[5]
    Hardware watchpoint 2: input[5]
    (gdb) i watchpoints
    Num Type Disp Enb Address What 2 hw watchpoint keep y input[5]
    (gdb) c
    Continuing. Hardware watchpoint 2: input[5]
    Old value = 0 '\0'
    New value = 1 '\001'
    0x0804840c in main () at main.c:11
    11 for (i = 0; input[i] != '\0'; i++)
    (gdb) c Continuing. Hardware watchpoint 2: input[5]
    Old value = 1 '\001'
    New value = 2 '\002' 0x0804840c in main () at main.c:11
    11 for (i = 0; input[i] != '\0'; i++)
    (gdb) c Continuing. Hardware watchpoint 2: input[5]
    Old value = 2 '\002'
    New value = 3 '\003' 0x0804840c in main () at main.c:11
    11 for (i = 0; input[i] != '\0'; i++)

已经很明显了，每次都是回到 for 循环开头的时候改变了 ``input[5]`` 的值，而且是每次加 1 ，而循环变量 i 正是在每次回到循环开头之前加 1 ，原来 ``input[5]`` 就是变量 ``i`` 的存储单元，换句话说， ``i`` 的存储单元是紧跟在 ``input`` 数组后面的。

修正这个 Bug 对初学者来说有一定难度。如果你发现了这个 Bug 却没想到数组访问越界这一点，也许一时想不出原因，就会先去处理另外一个更容易修正的 Bug ：如果输入的不是数字而是字母或别的符号也能算出结果来，这显然是不对的，可以在循环中加上判断条件检查非法字符：

.. code-block:: c

    while (1) {
        sum = 0;
        scanf("%s", input);
        for (i = 0; input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                printf("Invalid input!\n");
                sum = -1;
                break;
            }
            sum = sum*10 + input[i] - '0';
        }
        printf("input=%d\n", sum);
    }

然后你会惊喜地发现，不仅输入字母会报错，输入超长也会报错：

.. code-block:: none

    $ ./main
    123a
    Invalid input!
    input=-1
    dead
    Invalid input!
    input=-1
    1234578
    Invalid input!
    input=-1
    1234567890abcdef
    Invalid input!
    input=-1
    23
    input=23

似乎是两个 Bug 一起解决掉了，但这是治标不治本的解决方法。看起来输入超长的错误是不出现了，但只要没有找到根本原因就不可能真的解决掉，等到条件一变，它可能又冒出来了，在下一节你会看到它又以一种新的形式冒出来了。现在请思考一下为什么加上检查非法字符的代码之后输入超长也会报错。最后总结一下本节用到的 gdb 命令：

.. table:: gdb基本命令3
    :name: gdb基本命令3

    ======================= ================================================
    命令                    描述
    ----------------------- ------------------------------------------------
    watch                   设置观察点
    info（或i） watchpoints 查看当前设置了哪些观察点
    x                       从某个位置开始打印存储单元的内容，全部当成字节来
                            看，而不区分哪个字节属于哪个变量
    ======================= ================================================

.. [#F21] 不得不承认，在有些平台和操作系统上也未必得到这个结果，产生Bug的往往都是一些平台相关的问题，举这样的例子才比较像是真实软件开发中遇到的Bug，如果您的程序跑不出我这样的结果，那这一节您就凑合着看吧。

.. [#F22] 打印结果最左边的一长串数字是内存地址，在 :ref:`内存与地址` 详细解释，目前可以无视。

段错误
======

如果程序运行时出现段错误，用 gdb 可以很容易定位到究竟是哪一行引发的段错误，例如这个小程序：


.. code-block:: c
    :name: 段错误调试实例一

    #include <stdio.h>

    int main(void)
    {
        int man = 0;
        scanf("%d", man);
        return 0;
    }


调试过程如下：

.. code-block:: none

    $ gdb main
    ...
    (gdb) r
    Starting program: /home/akaedu/main
    123

    Program received signal SIGSEGV, Segmentation fault.
    0xb7e1404b in _IO_vfscanf () from /lib/tls/i686/cmov/libc.so.6
    (gdb) bt
    #0  0xb7e1404b in _IO_vfscanf () from /lib/tls/i686/cmov/libc.so.6
    #1  0xb7e1dd2b in scanf () from /lib/tls/i686/cmov/libc.so.6
    #2  0x0804839f in main () at main.c:6

在 gdb 中运行，遇到段错误会自动停下来，这时可以用命令查看当前执行到哪一行代码了。 gdb 显示段错误出现在 ``_IO_vfscanf`` 函数中，用 ``bt`` 命令可以看到这个函数是被我们的 ``scanf`` 函数调用的，所以是 ``scanf`` 这一行代码引发的段错误。仔细观察程序发现是 ``man`` 前面少了个 ``&`` 。

继续调试上一节的程序，上一节最后提出修正 Bug 的方法是在循环中加上判断条件，如果不是数字就报错退出，不仅输入字母可以报错退出，输入超长的字符串也会报错退出。表面上看这个程序无论怎么运行都不出错了，但假如我们把 ``while (1)`` 循环去掉，每次执行程序只转换一个数：

.. code-block:: c
    :name: 段错误调试实例二

    #include <stdio.h>

    int main(void)
    {
        int sum = 0, i = 0;
        char input[5];

        scanf("%s", input);
        for (i = 0; input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                printf("Invalid input!\n");
                sum = -1;
                break;
            }
            sum = sum*10 + input[i] - '0';
        }
        printf("input=%d\n", sum);
        return 0;
    }


然后输入一个超长的字符串，看看会发生什么：

.. code-block:: none

    $ ./main
    1234567890
    Invalid input!
    input=-1

看起来正常。再来一次，这次输个更长的：

.. code-block:: none

    $ ./main
    1234567890abcdef
    Invalid input!
    input=-1
    Segmentation fault

又出段错误了。我们按同样的方法用 gdb 调试看看：

.. code-block:: none

    $ gdb main
    ...
    (gdb) r
    Starting program: /home/akaedu/main
    1234567890abcdef
    Invalid input!
    input=-1

    Program received signal SIGSEGV, Segmentation fault.
    0x0804848e in main () at main.c:19
    19	}
    (gdb) l
    14			}
    15			sum = sum*10 + input[i] - '0';
    16		}
    17		printf("input=%d\n", sum);
    18		return 0;
    19	}

gdb 指出，段错误发生在第 19 行。可是这一行什么都没有啊，只有表示 main 函数结束的 ``}`` 括号。这可以算是一条规律， **如果某个函数的局部变量发生访问越界，有可能并不立即产生段错误，而是在函数返回时产生段错误** 。

想要写出 Bug-free 的程序是非常不容易的，即使 ``scanf`` 读入字符串这么一个简单的函数调用都会隐藏着各种各样的错误，有些错误现象是我们暂时没法解释的：为什么变量 ``i`` 的存储单元紧跟在 ``input`` 数组后面？为什么同样是访问越界，有时出段错误有时不出段错误？为什么访问越界的段错误在函数返回时才出现？还有最基本的问题，为什么 ``scanf`` 输入整型变量就必须要加 ``&`` ，否则就出段错误，而输入字符串就不要加 ``&`` ？这些问题在后续章节中都会解释清楚。其实现在讲 ``scanf`` 这个函数为时过早，读者还不具备充足的基础知识。但还是有必要讲的，学完这一阶段之后读者应该能写出有用的程序了，然而一个只有输出而没有输入的程序算不上是有用的程序，另一方面也让读者认识到， **学C语言不可能不去了解底层计算机体系结构和操作系统的原理** ，不了解底层原理连一个 ``scanf`` 函数都没办法用好，更没有办法保证写出正确的程序。
