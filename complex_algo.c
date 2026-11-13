/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:36:17 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/07 14:36:25 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	complex_algo(t_stack **a, t_stack **b)
{
	int	bit;
	int	i;
	int	size;

	if (!a || !b || !*a || is_sorted(*a))
		return ;
	get_ranked(*a);
	size = (int)calc_size(*a);
	bit = 0;
	while ((size - 1) >> bit) // 4 3 1 2 11 11 1 10
	{
		i = 0;
		while (i++ < size)
		{
			if (((*a)->rank >> bit) & 1)
				ra(a);
			else
				pb(a, b);
		}
		restore_binary(a, b);
		bit++;
	}
}