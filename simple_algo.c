/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   simple_algo.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 11:32:39 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/13 11:35:05 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_cases(t_stack **a, int f, int s, int t)
{
	if (f > s && s < t && f < t) // 2 1 3 with sa = 123 321
		sa(a);
	else if (f > s && s > t) //3 2 1  with sa = 231 rra = 123
	{
		sa(a);
		rra(a);
	}
	else if (f > s && s < t && f > t) // 3 1 2  ra = 123
		ra(a);
	else if (f < s && s > t && f < t)// 1 3 2 sa = 3 1 2 ra = 123
	{
		sa(a);
		ra(a);
	}
	else if (f < s && s > t && f > t) // 2 3 1 rra = 123
		rra(a);
}

void	simple_algo(t_stack **a, t_stack **b)
{
	int	f;
	int	s;
	int	t;

	(void) b;
	if (calc_size(*a) == 2)
		return (sa(a));
	f = (*a)->rank;
	s = (*a)->next->rank;
	t = (*a)->next->next->rank;
	sort_three_cases(a, f, s, t);
}
