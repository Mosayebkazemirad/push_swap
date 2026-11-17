/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 20:50:12 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:43 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sortiert einen kompletten Dreierstapel A aufsteigend.
** Hier sind ra / rra erlaubt, weil A nur drei Werte hat. */
void	sort_three_a(t_stack **a)
{
	int	x;
	int	y;
	int	z;

	x = (*a)->rank;
	y = (*a)->next->rank;
	z = (*a)->next->next->rank;
	if (x > y && y > z)
	{
		sa(a);
		rra(a);
	}
	else if (x > y && x > z)
		ra(a);
	else if (x < y && x < z && y > z)
	{
		sa(a);
		ra(a);
	}
	else if (x > y && x < z)
		sa(a);
	else if (x < y && x > z)
		rra(a);
}

/* Sortiert einen kompletten Dreierstapel B absteigend.
** Das erleichtert das spaetere Zurueckholen nach A. */
void	sort_three_b(t_stack **b)
{
	int	x;
	int	y;
	int	z;

	x = (*b)->rank;
	y = (*b)->next->rank;
	z = (*b)->next->next->rank;
	if (x < y && y < z)
	{
		sb(b);
		rrb(b);
	}
	else if (x < y && x < z)
		rb(b);
	else if (x > y && x > z && y < z)
	{
		sb(b);
		rb(b);
	}
	else if (x < y && x > z)
		sb(b);
	else if (x > y && x < z)
		rrb(b);
}

/* Sortiert nur die ersten drei A-Knoten aufsteigend.
** Nutzt pb/pa statt ra, damit der Rest unberuehrt bleibt. */
void	sort_three_top_a(t_stack **a, t_stack **b)
{
	if ((*a)->rank > (*a)->next->rank)
		sa(a);
	if ((*a)->next->rank > (*a)->next->next->rank)
	{
		pb(a, b);
		sa(a);
		pa(a, b);
	}
	if ((*a)->rank > (*a)->next->rank)
		sa(a);
}

/* Sortiert nur die ersten drei B-Knoten absteigend.
** Nutzt pa/pb statt rb, damit der Rest unberuehrt bleibt. */
void	sort_three_top_b(t_stack **a, t_stack **b)
{
	if ((*b)->rank < (*b)->next->rank)
		sb(b);
	if ((*b)->next->rank < (*b)->next->next->rank)
	{
		pa(a, b);
		sb(b);
		pb(a, b);
	}
	if ((*b)->rank < (*b)->next->rank)
		sb(b);
}
