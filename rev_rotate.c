/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   rev_rotate.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/05 12:30:58 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/05 12:30:58 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Verschiebt alle Elemente des Stacks um eins nach unten.
 Das letzte Element wird zum ersten. */

static void	rev_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = *stack;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

/* Führt rev_rotate für Stack A aus und gibt "rra" aus. */

void	rra(t_stack **stack_a)
{
	rev_rotate(stack_a);
	ft_putstr("rra\n");
}

/* Führt rev_rotate für Stack B aus und gibt "rrb" aus. */

void	rrb(t_stack **stack_b)
{
	rev_rotate(stack_b);
	ft_putstr("rrb\n");
}

/* Führt rra und rrb gleichzeitig aus und gibt "rrr" aus. */

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	ft_putstr("rrr\n");
}
