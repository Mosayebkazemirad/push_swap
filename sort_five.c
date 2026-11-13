/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:03:24 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/06 14:44:48 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_rank_pos(t_stack *a, int target_rank)
{
	int	pos;

	pos = 0;
	while (a)
	{
		if (a->rank == target_rank)
			return (pos);
		pos++;
		a = a->next;
	}
	return (0);
}

static void	push_smallest_to_b(t_stack **a, t_stack **b, int target_rank)
{
	int	pos;
	int	size;

	size = (int)calc_size(*a);
	pos = find_rank_pos(*a, target_rank);
	if (pos <= size / 2)
		while ((*a)->rank != target_rank)
			ra(a);
	else
		while ((*a)->rank != target_rank)
			rra(a);
	pb(a, b);
}

void	sort_five(t_stack **a, t_stack **b)
{
	int	target;

	target = 0;
	while (calc_size(*a) > 3)
	{
		push_smallest_to_b(a, b, target);
		target++;
	}
	simple_algo(a, b);
	while (*b)
		pa(a, b);
}