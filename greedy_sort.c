/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   greedy_sort.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 20:56:14 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:45 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Ein Durchlauf ueber die urspruengliche Laenge von A.
** keep = 1: ra erhaelt die Reihenfolge in A.
** keep = 0: pb verschiebt das Element nach B.
** Ein Durchlauf = genau eine ausgegebene Operation. */

static int	push_unmarked(t_stack **a, t_stack **b, t_sort_mark *work)
{
	int	n;
	int	i;

	n = calc_size(*a);
	i = 0;
	while (i++ < n)
	{
		if (work[(*a)->rank].keep)
			ra(a);
		else
			pb(a, b);
	}
	return (n);
}

/* Waehlt wiederholt den guenstigsten Kandidaten aus B.
** move.cost zaehlt nur Rotationen; pa kostet +1.
** Bei einem gesetzten Limit kann die Funktion abbrechen. */

static int	insert_cheapest(t_stack **a, t_stack **b, long *count, long limit)
{
	t_sort_move	move;

	while (*b)
	{
		move = cheapest_move(*a, *b);
		if (limit > 0 && *count + move.cost + 1 > limit)
			return (0);
		do_move(a, b, move);
		pa(a, b);
		*count += move.cost + 1;
	}
	return (1);
}

/* Nach dem Einfuegen ist A eventuell nur zyklisch sortiert.
** Dreht Rang 0 mit der kuerzeren Richtung nach oben.
** Bei Medium wird vorher das Operationslimit geprueft. */

static int	finish_greedy(t_stack **a, long *used, long limit)
{
	t_stack	*node;
	int		index;
	int		rotation;

	index = 0;
	node = *a;
	while (node && node->rank != 0)
	{
		index++;
		node = node->next;
	}
	rotation = calc_rota_pos(index, calc_size(*a));
	if (limit > 0 && *used + abs_steps(rotation) > limit)
		return (0);
	rotate_a(a, rotation);
	return (1);
}

/* Simple und Medium teilen sich das Einfuegen, nicht die Auswahl.
** run = 0: LIS, run = 1: zusammenhaengender Lauf.
** limit = 0: unbegrenzt; sonst maximal so viele Roh-Operationen.
** Rueckgabe 0: malloc fehlgeschlagen oder Budget verbraucht.
** Beim Budget-Abbruch koennen noch Werte auf B liegen. */

int	sort_greedy(t_stack **a, t_stack **b, long limit, int run)
{
	t_sort_mark	*work;
	long		used;
	int			size;
	int			result;

	size = calc_size(*a);
	work = malloc(sizeof(*work) * (size_t) size);
	if (!work)
		return (0);
	if (run)
		mark_run(*a, work, size);
	else
		mark_lis(*a, work, size);
	used = push_unmarked(a, b, work);
	free(work);
	result = (limit == 0 || used <= limit);
	if (result)
		result = insert_cheapest(a, b, &used, limit);
	if (result)
		result = finish_greedy(a, &used, limit);
	return (result);
}
