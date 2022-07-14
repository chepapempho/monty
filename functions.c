#include "monty.h"

/**
 * free_malloc - free stack to memory.
 * @head: pointer to head of the stack.
 * Return: void.
 */

void free_malloc(stack_t *head)
{
	stack_t *lista = head;

	if (head == NULL)
	{
		return;
	}
	while (head != NULL)
	{
		lista = head;
		head = head->next;
		free(lista);
	}
}
/**
 * functions_monty - compare the opcodes and run the function asociate.
 * @stack: poiter to head of the stack.
 * @command_f: pass string to command of function.
 * @line_numb: line number in file.
 * Return: void.
 */
void functions_monty(stack_t **stack, char *command_f, unsigned int line_numb)
{
	instruction_t funct_monty[] = {
		{"pall", pall}, {"push", push}, {"pint", pint},
		{"pop", pop}, {"swap", swap}, {"add", add},
		{"nop", nop}, {"sub", sub}, {"div", _div},
		{"mul", mul}, {"mod", mod}, {NULL, NULL}};
	unsigned int i = 0;
	int checker = 0;

	while (i < 11 && command_f != NULL)
	{
		if (command_f[0] == '#')
			break;
		if (strcmp(funct_monty[i].opcode, command_f) == 0)
		{
			funct_monty[i].f(stack, line_numb);
			checker = 1;
			break;
		}
		i++;
	}
	if (checker == 0 && command_f[0] != '#')
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_numb, command_f);
		free(command_f);
		var_glob[1] = 1;
		exit(EXIT_FAILURE);
	}
}
/**
 * nop - doesn't do anything.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * pall - print all elements of stack.
 * @stack: pointer head stack.
 * @line_number: files line number.
 * Return: the number of nodes.
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *h = *stack;
	(void)line_number;
	while (h != NULL)
	{
		printf("%i\n", h->n);
		h = h->next;
	}
}

/**
 * push - Implement the pint opcode.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: nothing.
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *node = NULL;
	stack_t *copy = *stack;
	(void)line_number;

	if (stack == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		var_glob[1] = 1;
		return;
	}
	node = malloc(sizeof(stack_t));
	if (node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(stack);
		var_glob[1] = 1;
		return;
	}
	node->prev = NULL;
	node->n = var_glob[0];
	node->next = *stack;
	if (*stack)
		copy->prev = node;
	*stack = node;
}
/**
 * pint - Implement the pint opcode.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: nothing.
 */

void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		var_glob[1] = 1;
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - remove a element to the top of stack.
 * @stack: pointer to head of stack.
 * @line_number: files line number.
 * Return: void.
 */

void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *node = *stack;

	if ((*stack) == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		free(stack);
		var_glob[1] = 1;
		return;
	}
	if (node)
	{

		*stack = (node)->next;
		free(node);
	}
}

/**
 * swap - swap two element in stack.
 * @stack: pointer to head of stack.
 * @line_number: files line number.
 * Return: void.
 */

void swap(stack_t **stack, unsigned int line_number)
{
	int i, j = 0;
	stack_t *copy_stack = *stack;

	while (copy_stack != NULL)
	{
		i++;
		copy_stack = copy_stack->next;
	}
	if (i < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free(stack);
		var_glob[1] = 1;
		return;
	}
	j = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = j;
}


/**
 * add - add two element to the top of the stack.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */

void add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		var_glob[1] = 1;
		return;
	}
	(*stack)->next->n = (*stack)->n + (*stack)->next->n;
	pop(stack, line_number);
}

/**
 * sub - substracts the top elements of the stack.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */

void sub(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		var_glob[1] = 1;
		return;
	}
	(*stack)->next->n = (*stack)->next->n - (*stack)->n;
	pop(stack, line_number);
}
/**
 * _div - divides the second top elements of the stack.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */

void _div(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		var_glob[1] = 1;
		return;
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		var_glob[1] = 1;
		return;
	}
	(*stack)->next->n = (*stack)->next->n / (*stack)->n;
	pop(stack, line_number);
}

/**
 * mul - multiplies the second top elements of the stack.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */

void mul(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		var_glob[1] = 1;
		return;
	}
	(*stack)->next->n = (*stack)->next->n * (*stack)->n;
	pop(stack, line_number);
}

/**
 * mod - computes the rest off the division of the second top elements stack.
 * @stack: pointer head stack.
 * @line_number: line number in file.
 * Return: void.
 */

void mod(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		var_glob[1] = 1;
		return;
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		var_glob[1] = 1;
		return;
	}
	(*stack)->next->n = (*stack)->next->n % (*stack)->n;
	pop(stack, line_number);
}

/**
 * f_pchar - prints the char at the top of the stack,
 * followed by a new line
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void _pchar(stack_t **head, unsigned int counter)
{
	stack_t *h;

	h = *head;
	if (!h)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	if (h->n > 127 || h->n < 0)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", h->n);
}

/**
 * f_pchar - prints the char at the top of the stack,
 * followed by a new line
 * @head: stack head
 * @counter: line_number
 * Return: no return
*/
void _pchar(stack_t **head, unsigned int counter)
{
	stack_t *h;

	h = *head;
	if (!h)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	if (h->n > 127 || h->n < 0)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", h->n);
}
