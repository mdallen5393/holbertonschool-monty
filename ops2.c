#include "monty.h"
/**
 * pall - prints all elements of a stack
 * @stack: linked list stack to pall
 * @line_number: current line number of bytecode file
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void)line_number;
	temp = *stack;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * swap - swaps the two top elements of a stack
 * @stack: linked list stack to swap
 * @line_number: current line number of bytecode file
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp = (*stack)->n;

	if (!(*stack) || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

/**
 * add - adds the first two elements of a stack, replaces both with sum
 * @stack: linked list stack to add
 * @line_number: current line number of bytecode file
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (!temp || !temp->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_stack(stack);
		err();
	}

	temp->next->n += temp->n;
	*stack = temp->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * nop - does nothing
 * @stack: linked list stack to do nothing to
 * @line_number: current line number of bytecode file
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
