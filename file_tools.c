#include "monty.h"

/**
 * open_thefile - opens a file
 * @file_name: the file namepath
 * Return: void
 */

void open_thefile(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		errr(2, file_name);

	read_thefile(fd);
	fclose(fd);
}


/**
 * read_thefile - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void read_thefile(FILE *fd)
{
	int line_numb, format = 0;
	char *buffer = NULL;
	size_t leng = 0;

	for (line_numb = 1; getline(&buffer, &leng, fd) != -1; line_numb++)
	{
		format = parse_line(buffer, line_numb, format);
	}
	free(buffer);
}


/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @line_number: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		errr(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_thefunc(opcode, value, line_number, format);
	return (format);
}

/**
 * find_thefunc - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_thefunc(char *opcode, char *value, int ln, int format)
{
	int j;
	int rflag;

	instruction_t func_list[] = {
		{"push", addto_stack},
		{"pall", print_thestack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", modf_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (rflag = 1, j = 0; func_list[j].opcode != NULL; j++)
	{
		if (strcmp(opcode, func_list[j].opcode) == 0)
		{
			call_thefun(func_list[j].f, opcode, value, ln, format);
			rflag = 0;
		}
	}
	if (rflag == 1)
		errr(3, ln, opcode);
}


/**
 * call_thefun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_thefun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int rflag;
	int j;

	rflag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			rflag = -1;
		}
		if (val == NULL)
			errr(5, ln);
		for (j = 0; val[j] != '\0'; j++)
		{
			if (isdigit(val[j]) == 0)
				errr(5, ln);
		}
		node = create_node(atoi(val) * rflag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
