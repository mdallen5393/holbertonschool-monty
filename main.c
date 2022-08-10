#include "monty.h"

FILE *file = NULL;
/**
 * main - runs monty bytecode interpreter
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	void (*f)(stack_t **, unsigned int) = NULL;
	char *buffer = NULL, op[50], pushNum[50];
	size_t bufsize = 0;
	stack_t **stack = NULL;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (getline(&buffer, &bufsize, file) != -1)
	{
		strcpy(op, strtok(buffer, " \t\n"));
		f = get_func(op, line_number);
		if (!f)
		{
			fprintf(stderr, "Error: malloc failed\n");
			fclose(file);
			exit(EXIT_FAILURE);
		}
		if (strcmp(op, "push"))
			strcpy(pushNum, strtok(NULL, " \t\n"));
		free(buffer);
		buffer = NULL;
		f(stack, line_number);
		if (strcmp(op, "push") == 0)
		{
			if (strcmp(pushNum, "0") == 0)
				(*stack)->n = 0;
			if (strcmp(pushNum, "0") != 0)
			{
				(*stack)->n = atoi(pushNum);
				if ((*stack)->n == 0)
				{
					fprintf(stderr, "Error: L%d: usage: push integer", line_number);
					fclose(file);
					exit(EXIT_FAILURE);
				}
			}
		}
		line_number++;
	}
	return (0);
}


 /**
 * get_func - finds function to use to execute the desired opcode
 * @opcode: string used to find correct function
 * Return: pointer to desired function
 */
void (*get_func(char *opcode, int line_number))(stack_t **, unsigned int)
{
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop}
	};
	int i = 0;

	while (strcmp(opcode, instruction[i].opcode) != 0)
	{
		if (i > 7)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			fclose(file);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (instruction[i].f);
}
