#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int top;      // 栈的当前层数
  int length;   // 栈的最大深度
  char *body;   // 存储实际数据
} char_stack_t;

// 栈的实例化
int new (char_stack_t *);
// 栈的析构
int delete (char_stack_t *);

/* 栈的标志行为 -- push， pop */
int push(char_stack_t *, char);
/* 用指针接收值， 返回值用于传递错误码 */
int pop(char_stack_t *, char *);

int main(int argc, char const *argv[]) {
  char_stack_t stack;
  new (&stack);

  char *string = "abcdefghij";
  for (int i = 0; i < 10; ++i) {
    push(&stack, string[i]);
  }
  for (char i; pop(&stack, &i) == 0;) {
    putchar(i);
  }
  putchar('\n');

  delete (&stack);
  return 0;
}

int push(char_stack_t *stack, char item) {
  if (stack->top < stack->length - 1) {
      // 入栈前, 先向后运动一位
    ++stack->top;
    stack->body[stack->top] = item;
    return 0;
  } else {
    return -1; // 栈已满
  }
}

int pop(char_stack_t *stack, char *result) {
  if (stack->top >= 0) {
    *result = stack->body[stack->top];
    // 出栈后, 再向前运动一位
    --stack->top;
    return 0;
  } else {
    return -1; // 栈已空
  }
}

int new (char_stack_t *stack) {
  stack->body = calloc(100, sizeof(char));
  if (stack->body != NULL) {
    stack->top = -1; // -1 表示空
    stack->length = 100;
    return 0;
  } else {
    return -1; // 内存分配失败
  }
}

int delete (char_stack_t *stack) {
  free(stack->body);
  stack->top = -1;
  stack->length = 0;
  return 0;
}
