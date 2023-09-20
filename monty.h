#ifndef MONTY_H
#define MONTY_H

/**
 * struct stack_s - Represents a stack node.
 * @n: Integer value stored in the node.
 * @next: Pointer to the next node in the stack.
 */
typedef struct stack_s {
    int n;
    struct stack_s *next;
} stack_t;

/* Function prototypes for opcode functions */
void push(stack_t **stack, int value);
void pall(stack_t *stack);

/* Add more function prototypes for other opcodes here */

void parse_and_execute(FILE *file, stack_t **stack);
void free_stack(stack_t *stack);

#endif /* MONTY_H */
