#ifndef OPERASJONER_H_
#define OPERASJONER_H_

#include "stack.h"

void stack_add(stack_t *stack);

void stack_minus(stack_t *stack);

void stack_multi(stack_t *stack);

void stack_divide(stack_t *stack);

void stack_modulo(stack_t *stack);

void stack_equal(stack_t *stack);

void stack_greater(stack_t *stack);

void stack_dup(stack_t *stack);

void stack_swap(stack_t *stack);

void stack_cjump(stack_t *stack, int *pc);

void stack_print(stack_t *stack);

void stack_newline();

#endif