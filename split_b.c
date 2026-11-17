/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 20:56:14 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:46 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sortiert kleine obere Gruppen von B absteigend und
** schiebt sie mit pa in die korrekte A-Reihenfolge. */
static void	quick_b_small(t_stack **a, t_stack **b, int n, int low)
{
	if (n == 1)
		pa(a, b);
	else if (n == 2)
	{
		if ((*b)->rank < (*b)->next->rank)
			sb(b);
		pa(a, b);
		pa(a, b);
	}
	else if (n == 3)
	{
		if (calc_size(*b) == 3)
			sort_three_b(b);
		else
			sort_three_top_b(a, b);
		pa(a, b);
		pa(a, b);
		pa(a, b);
	}
	else if (n == 4)
		sort_four_b(a, b, low);
}

/* Nur die ersten n Knoten gehoeren zu diesem rekursiven Bereich.
** Hohe Raenge gehen mit pa nach A, niedrige rotieren in B.
** Liegen darunter andere Gruppen, muessen ihre Positionen durch
** die Gegenrotationen wiederhergestellt werden. */
static int	partition_b(t_stack **a, t_stack **b, int n, int pivot)
{
	int	low_count;
	int	i;
	int	extra;

	extra = (calc_size(*b) > n);
	low_count = 0;
	i = 0;
	while (i++ < n)
	{
		if ((*b)->rank >= pivot)
			pa(a, b);
		else
		{
			rb(b);
			low_count++;
		}
	}
	if (extra)
		while (low_count-- > 0)
			rrb(b);
	return (n / 2);
}

/* Rekursiver B-Zweig: groessere Raenge nach A aufbauen,
** danach kleinere Raenge verarbeiten und darueber legen. */
void	split_b(t_stack **a, t_stack **b, int count, int low)
{
	int	pivot;
	int	low_count;

	if (count < 1)
		return ;
	if (count <= 4)
	{
		quick_b_small(a, b, count, low);
		return ;
	}
	pivot = low + count / 2;
	low_count = partition_b(a, b, count, pivot);
	split_a(a, b, count - low_count, pivot);
	split_b(a, b, low_count, low);
}
