/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:20:53 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/13 12:22:16 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	select_algo(t_stack **a, t_stack **b, int size)
{
	if (size <= 3)
		simple_algo(a, b);
	/*5 möglichkeiten 132 213 231 312 312 */
	else if (size <= 5)
		sort_five(a, b);
	else if (size <= 100)
		medium_algo(a, b);
	else
		complex_algo(a, b);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_b = NULL;
	stack_a = input_check(argc, argv);
	if (!stack_a)
		return (1);
	get_ranked(stack_a);
	if (!is_sorted(stack_a))
		select_algo(&stack_a, &stack_b, (int) calc_size(stack_a));
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
