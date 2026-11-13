/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:40:44 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/05 11:54:08 by mkazemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Gibt den zugewiesenen Speicher für den gesamten Stack frei. */
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;
	t_stack	*current;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

/* Erstellt einen neuen Knoten und fügt ihn am Ende des Stacks hinzu. */
static void	add_node_to_stack(t_stack **stack, int num)
{
	t_stack	*new_node;
	t_stack	*last;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return ;
	new_node->n = num;
	new_node->next = NULL;
	if (*stack == NULL)
	{
		*stack = new_node;
	}
	else
	{
		last = *stack;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

/* Überprüft, ob der übergebene String eine gültige Zahl enthält. */
static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

/* Überprüft, ob eine bestimmte Zahl bereits im Stack vorhanden ist. */
static int	is_duplicate(t_stack *stack, int num)
{
	t_stack	*current;

	current = stack;
	while (current != NULL)
	{
		if (current->n == num)
			return (1);
		current = current->next;
	}
	return (0);
}

/* Überprüft die Eingabeargumente, erstellt den Stack A und behandelt Fehler. */
t_stack	*input_check(int argc, char **argv)
{
	t_stack		*stack_a;
	int			i;
	long int	num;

	stack_a = NULL;
	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
		{
			ft_putstr("Error\n");
			free_stack(&stack_a);
			exit(1);
		}
		num = ft_atoi(argv[i]);
		if (num > INT_MAX || num < INT_MIN || is_duplicate(stack_a, (int) num))
		{
			ft_putstr("Error\n");
			free_stack(&stack_a);
			exit(1);
		}
		add_node_to_stack(&stack_a, (int) num);
		i++;
	}
	return (stack_a);
}
