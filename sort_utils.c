/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:32:34 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/07 14:36:51 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

unsigned int	calc_size(t_stack *stack)
{
	unsigned int	count;

	count = 0;
	while (stack != NULL)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

int	calc_rota(t_stack *stack, int rank)
{
	int	index;
	int	size;

	size = (int)calc_size(stack);
	index = 0;
	while (stack && stack->rank != rank)
	{
		index++;
		stack = stack->next;
	}
	if (!stack)
		return (INT_MAX);
	if (index > size / 2)
		return (index - size);
	return (index);
}

int	get_chunk_size(int n)
{
	int	size;

	size = 1;
	while ((long)size * size < n)
		size++;
	return (size);
}

void	restore_binary(t_stack **a, t_stack **b)
{
	while (*b)
		pa(a, b);
}
mosaunbd
