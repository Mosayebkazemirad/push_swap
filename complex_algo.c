/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   complex_algo.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/07 14:36:17 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/10 08:39:34 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	complex_algo(t_stack **a, t_stack **b, int size)
{
	int	bit;
	int	i;

	if (!a || !b || !*a || is_sorted(*a))
		return ;
	bit = 0;
	while ((size - 1) >> bit)
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
