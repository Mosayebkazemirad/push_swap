/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   find_lis.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/12 14:57:28 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:37 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* LIS: laengste aufsteigende Teilfolge, ohne Knoten zu verschieben. */

/* Setzt alle Hilfsdaten zurueck: length = Laenge der Folge,
** parent = Vorgaenger, keep = bleibt spaeter in A. */

static void	initialize_lis(t_sort_mark *work, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		work[i].length = 0;
		work[i].parent = -1;
		work[i].keep = 0;
		i++;
	}
}

/* Prueft fuer den aktuellen Knoten alle vorherigen Knoten.
** Nur kleinere Raenge koennen Vorgaenger der LIS sein.
** Der beste Vorgaenger wird ueber parent gespeichert. */

static void	update_lis(t_stack *head, t_stack *node, t_sort_mark *work)
{
	t_stack	*scan;
	int		current;
	int		prior;

	current = node->rank;
	work[current].length = 1;
	scan = head;
	while (scan != node)
	{
		prior = scan->rank;
		if (prior < current
				&& work[prior].length + 1 > work[current].length)
		{
			work[current].length = work[prior].length + 1;
			work[current].parent = prior;
		}
		scan = scan->next;
	}
}

/* Berechnet die laengste aufsteigende Teilfolge in A.
** Danach folgt es parent rueckwaerts und markiert alle
** behaltenen Raenge mit keep = 1. */

void	mark_lis(t_stack *a, t_sort_mark *work, int size)
{
	t_stack	*node;
	int		best;
	int		length;

	initialize_lis(work, size);
	best = -1;
	length = 0;
	node = a;
	while (node)
	{
		update_lis(a, node, work);
		if (work[node->rank].length > length)
		{
			length = work[node->rank].length;
			best = node->rank;
		}
		node = node->next;
	}
	while (best >= 0)
	{
		work[best].keep = 1;
		best = work[best].parent;
	}
}
