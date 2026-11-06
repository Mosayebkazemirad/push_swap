/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/05 07:57:14 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/05 11:54:57 by mkazemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Nimmt das erste Element von einem Quell-Stack und
 *  legt es auf den Ziel-Stack. */
static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*temp;

	if (!src || !*src)
		return ;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}

/* Verschiebt das oberste Element von Stack B auf Stack A und gibt "pa" aus. */
void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_b, stack_a);
	ft_putstr("pa\n");
}

/* Verschiebt das oberste Element von Stack A auf Stack B und gibt "pb" aus. */
void	pb(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);
	ft_putstr("pb\n");
}
