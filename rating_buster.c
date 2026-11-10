/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rating_buster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 09:51:21 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/06 10:01:50 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_ranked(t_stack *stack)
{
	t_stack	*current;
	t_stack	*compare;
	int		rank;

	if (!stack)
		return ;
	current = stack;
	while (current)
	{
		rank = 0;
		compare = stack->next; /*vieleicht beeser compare = stack->next; */
		while (compare)
		{
			if (compare->n < current->n) // 3 4 1 5 9 7
				rank++;
			compare = compare->next;
		}
		current->rank = rank;
		current = current->next;
	}
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->n > stack->next->n)
			return (0);
		stack = stack->next;
	}
	return (1);
}
