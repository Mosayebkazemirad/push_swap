/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:24:23 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:31 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Fehler niemals auf stdout schreiben: dort gehoeren nur Stack-OPs hin. */
void	ps_input_error(t_stack **stack)
{
	free_stack(stack);
	write(2, "Error\n", 6);
	exit(1);
}

/* Fuegt einen Knoten ans Ende von A an und sucht dabei Duplikate.
** Jeder neue Knoten startet mit rank = -1; Ranking erfolgt spaeter.
** Bei Fehler werden bereits angelegte Knoten freigegeben. */
void	ps_append_number(t_stack **stack, int number)
{
	t_stack	*node;
	t_stack	*last;

	last = *stack;
	while (last)
	{
		if (last->n == number)
			ps_input_error(stack);
		if (!last->next)
			break ;
		last = last->next;
	}
	node = malloc(sizeof(*node));
	if (!node)
		ps_input_error(stack);
	node->n = number;
	node->rank = -1;
	node->next = NULL;
	if (last)
		last->next = node;
	else
		*stack = node;
}
