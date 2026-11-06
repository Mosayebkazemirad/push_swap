/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/05 07:54:50 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/05 11:52:17 by mkazemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Vertauscht die ersten beiden Elemente an der Spitze eines Stacks. */
static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

/* Vertauscht die ersten beiden Elemente von Stack A und gibt "sa" aus. */
void	sa(t_stack **stack_a)
{
	swap(stack_a);
	ft_putstr("sa\n");
}

/* Vertauscht die ersten beiden Elemente von Stack B und gibt "sb" aus. */
void	sb(t_stack **stack_b)
{
	swap(stack_b);
	ft_putstr("sb\n");
}

/* Führt sa und sb gleichzeitig aus und gibt "ss" aus. */
void	ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	ft_putstr("ss\n");
}
