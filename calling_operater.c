/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calling_operater.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:41:57 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/06 11:03:37 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	call_rra(t_stack **a, int rota)
{
	int i;

	i = 0;
	while(i++ < rota)
		rra(a);
}

void	call_ra(t_stack **a, int rota)
{
	int i;

	i = 0;
	while(i++ < rota)
		ra(a);
}
