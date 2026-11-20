/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 09:40:44 by mkazemir          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:22 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Gibt auch bei einem Parserfehler alle bisherigen Knoten frei. */
void	free_stack(t_stack **stack)
{
	t_stack	*next;

	if (!stack)
		return ;
	while (*stack)
	{
		next = (*stack)->next;
		free(*stack);
		*stack = next;
	}
}

/* Ein Argument darf mehrere durch Leerraum getrennte Zahlen haben. */
static void	parse_argument(t_stack **stack, const char *str)
{
	int	number;
	int	found;

	found = 0;
	while (*str)
	{
		while (ps_is_space(*str))
			str++;
		if (!*str)
			break ;
		if (!ps_read_number(&str, &number))
			ps_input_error(stack);
		ps_append_number(stack, number);
		found = 1;
	}
	if (!found)
		ps_input_error(stack);
}

/* Baut A aus allen verbliebenen argv-Argumenten auf.
** Die eigentliche Zahlenpruefung uebernehmen die Parser-Helfer. */
t_stack	*input_check(int argc, char **argv)
{
	t_stack	*stack;
	int		i;

	stack = NULL;
	i = 1;
	while (i < argc)
		parse_argument(&stack, argv[i++]);
	return (stack);
}
