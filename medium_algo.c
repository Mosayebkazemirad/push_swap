/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 14:44:03 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/06 14:44:36 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	restore_a(t_stack **a, t_stack **b, int size)
{
	int	rota;

	while (*b)
	{
		rota = calc_rota(*b, size - 1);
		while (rota > 0)
		{
			rb(b);
			rota--;
		}
		while (rota < 0)
		{
			rrb(b);
			rota++;
		}
		pa(a, b);
		size--;
	}
}

static void	push_chunk(t_stack **a, t_stack **b, int min_rank,
		int chunk_size)
{
	int	count;

	count = 0;
	while (*a && count < chunk_size)
	{
		if ((*a)->rank >= min_rank
			&& (*a)->rank < min_rank + chunk_size)
		{
			pb(a, b);
			count++;
		}
		else
			ra(a);
	}
}

void	medium_algo(t_stack **a, t_stack **b)
{
	int	chunk_size;
	int	size;
	int	min_rank;

	if (!a || !b || !*a || is_sorted(*a))
		return ;
	get_ranked(*a);
	size = (int)calc_size(*a);
	chunk_size = get_chunk_size(size);
	min_rank = 0;
	while (min_rank < size)
	{
		push_chunk(a, b, min_rank, chunk_size);
		min_rank += chunk_size;
	}
	restore_a(a, b, size);
}
