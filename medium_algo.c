/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   medium_algo.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 12:12:42 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:55 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Ein aufsteigender Lauf endet, sobald der naechste Rang
** nicht groesser als der aktuelle Rang ist. */

static int	extend_run(t_stack *node, t_stack **start, int length)
{
	if (node->rank >= node->next->rank)
	{
		*start = node->next;
		return (1);
	}
	return (length + 1);
}

/* Findet den laengsten direkt zusammenhaengenden
** aufsteigenden Abschnitt (anders als eine LIS). */

static t_stack	*best_run(t_stack *a, int *best_length)
{
	t_stack	*node;
	t_stack	*start;
	t_stack	*best;
	int		length;

	best = a;
	start = a;
	length = 1;
	*best_length = 1;
	node = a;
	while (node->next)
	{
		length = extend_run(node, &start, length);
		if (length > *best_length)
		{
			best = start;
			*best_length = length;
		}
		node = node->next;
	}
	return (best);
}

/* Markiert alle Knoten des gefundenen Abschnitts.
** Im Unterschied zur LIS muessen sie nebeneinander stehen. */

void	mark_run(t_stack *a, t_sort_mark *work, int size)
{
	t_stack	*best;
	int		length;
	int		i;

	i = 0;
	while (i < size)
		work[i++].keep = 0;
	best = best_run(a, &length);
	while (length-- > 0)
	{
		work[best->rank].keep = 1;
		best = best->next;
	}
}

/* Natural-Run-Greedy darf hoechstens 12*n Roh-OPs verbrauchen.
** Falls das Budget nicht reicht oder malloc scheitert, wird B zuerst
** geleert und dann erneut mit sqrt(n)-Chunks sortiert.
** Wichtig: Der Chunk-Fallback startet mit allen Werten in A. */

void	medium_ranked(t_stack **a, t_stack **b)
{
	int	size;

	size = calc_size(*a);
	if (!sort_greedy(a, b, 12L * size, 1))
	{
		while (*b)
			pa(a, b);
		sort_chunks(a, b, size);
	}
}
