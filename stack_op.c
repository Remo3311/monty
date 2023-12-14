#include "monty.h"

/**
 * mul_nodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void mul_nodes(stack_t **stack, unsigned int line_number)
{
	int sumof;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mul");

	(*stack) = (*stack)->next;
	sumof = (*stack)->n * (*stack)->prev->n;
	(*stack)->n = sumof;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * modf_nodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void modf_nodes(stack_t **stack, unsigned int line_number)
{
	int sumof;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)

		more_err(8, line_number, "mod");


	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	sumof = (*stack)->n % (*stack)->prev->n;
	(*stack)->n = sumof;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
