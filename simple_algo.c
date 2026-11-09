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

void	simple_algo(t_stack **a, t_stack **b)
{
	int	rota;
	int	rank;
	int	size;

	if (!a || !b || !*a || is_sorted(*a))//0 1 2 3 4
		return ; 
	get_ranked(*a); //????
	size = (int)calc_size(*a);
	rank = 0;
	while (rank < size)
	{
		rota = calc_rota(*a, rank);
		if (rota > 0)
			call_ra(a, rota);
		else if (rota < 0)
			call_rra(a, -rota);
		pb(a, b);
		rank++;
	}
	while (*b)
		pa(a, b);
}

