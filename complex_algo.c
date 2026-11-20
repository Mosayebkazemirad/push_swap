/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   complex_algo.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 12:12:48 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:33 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sortiert eine kleine obere Teilgruppe von A.
** Bei 3/4 Werten darf der darunterliegende Rest
** nicht durch ra / rra durcheinander geraten. */

static void	quick_a_small(t_stack **a, t_stack **b, int n, int low)
{
	if (n == 2 && (*a)->rank > (*a)->next->rank)
		sa(a);
	else if (n == 3)
	{
		if (calc_size(*a) == 3)
			sort_three_a(a);
		else
			sort_three_top_a(a, b);
	}
	else if (n == 4)
		sort_four_a(a, b, low);
}

/* Teilt die ersten n Werte von A am Rang-Pivot.
** Kleine Raenge gehen nach B, grosse rotieren in A.
** Falls A mehr als n Werte enthaelt: Rotation korrigieren. */

static int	partition_a(t_stack **a, t_stack **b, int n, int pivot)
{
	int	kept;
	int	i;
	int	extra;

	extra = (calc_size(*a) > n);
	kept = 0;
	i = 0;
	while (i++ < n)
	{
		if ((*a)->rank < pivot)
			pb(a, b);
		else
		{
			ra(a);
			kept++;
		}
	}
	if (extra)
		while (kept-- > 0)
		rra(a);
	return (n - n / 2);
}

/* Rekursiver A-Zweig: Bereich teilen, zuerst den groesseren
** Rangbereich in A, danach den kleineren in B sortieren. */

void	split_a(t_stack **a, t_stack **b, int count, int low)
{
	int	pivot;
	int	high;

	if (count < 2)
		return ;
	if (count <= 4)
	{
		quick_a_small(a, b, count, low);
		return ;
	}
	pivot = low + count / 2;
	high = partition_a(a, b, count, pivot);
	split_a(a, b, high, pivot);
	split_b(a, b, count - high, low);
}

/* Rekursive Rangpartitionierung: je Ebene werden die Rangbereiche
** in etwa halbiert. Die Ausgabeoptimierung ist nur hier aktiv.
** Sie kuerzt Befehle, ohne die Sortierentscheidungen zu veraendern. */

void	complex_ranked(t_stack **a, t_stack **b)
{
	ps_opt_begin(*a);
	split_a(a, b, calc_size(*a), 0);
	ps_opt_finish(*a);
}
