#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * push - Pushes an element onto the stack.
 * @stack: Pointer to the top of the stack.
 * @value: Value to push.
 */
void push(stack_t **stack, int value)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->next = *stack;
    *stack = new_node;
}

/**
 * pall - Print all the values on the stack.
 * @stack: Pointer to the top of the stack.
 */
void pall(stack_t *stack)
{
    while (stack != NULL)
    {
        printf("%d\n", stack->n);
        stack = stack->next;
    }
}

/**
 * parse_and_execute - Parse and execute Monty bytecodes from a file.
 * @file: Pointer to the Monty bytecodes file.
 * @stack: Pointer to the top of the stack.
 */
void parse_and_execute(FILE *file, stack_t **stack)
{
    char opcode[128];
    int value;
    unsigned int line_number = 0;

    while (fgets(opcode, sizeof(opcode), file) != NULL)
    {
        line_number++;
        // Remove trailing newline character if present
        size_t opcode_len = strlen(opcode);
        if (opcode_len > 0 && opcode[opcode_len - 1] == '\n')
            opcode[opcode_len - 1] = '\0';

        // Tokenize and process opcodes here
        if (sscanf(opcode, "push %d", &value) == 1)
        {
            push(stack, value);
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(*stack);
        }
        // Add more opcode handling here based on your project's requirements
        else
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * free_stack - Free memory used by the stack.
 * @stack: Pointer to the top of the stack.
 */
void free_stack(stack_t *stack)
{
    while (stack != NULL)
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    stack_t *stack = NULL;

    // Parse and execute opcodes from the file
    parse_and_execute(file, &stack);

    fclose(file);
    free_stack(stack);

    return 0;
}
