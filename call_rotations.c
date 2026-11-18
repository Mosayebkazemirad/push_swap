/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_rotations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:36:14 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:21 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Positive Schritte: ra, negative Schritte: rra.
** Fuehrt genau so viele Rotationen wie angegeben aus. */
void	rotate_a(t_stack **a, int steps)
{
	while (steps > 0)
	{
		ra(a);
		steps--;
	}
	while (steps < 0)
	{
		rra(a);
		steps++;
	}
}

/* Positive Schritte: rb, negative Schritte: rrb.
** Fuehrt genau so viele Rotationen wie angegeben aus. */
void	rotate_b(t_stack **b, int steps)
{
	while (steps > 0)
	{
		rb(b);
		steps--;
	}
	while (steps < 0)
	{
		rrb(b);
		steps++;
	}
}

/* Beide Stacks gleichgerichtet: rr / rrr spart Schritte.
** Dann ist die Kostenanzahl das Maximum beider Wege.
** Sonst muessen die Einzelschritte addiert werden. */
int	move_cost(int a_steps, int b_steps)
{
	int	a_cost;
	int	b_cost;
			//sort_utils
	a_cost = abs_steps(a_steps);
	b_cost = abs_steps(b_steps);
	if (a_steps > 0 && b_steps > 0)
	{
		if (a_cost > b_cost)
			return (a_cost);
		return (b_cost);
	}
	if (a_steps < 0 && b_steps < 0)
	{
		if (a_cost > b_cost)
			return (a_cost);
		return (b_cost);
	}
	return (a_cost + b_cost);
}

/* Fuehrt zuerst gemeinsame rr-/rrr-Schritte aus und
** anschliessend die uebrigen Einzelrotationen.
** pa folgt erst beim Aufrufer insert_cheapest. */
void	do_move(t_stack **a, t_stack **b, t_sort_move move)
{
	while (move.ra > 0 && move.rb > 0)
	{
		rr(a, b);
		move.ra--;
		move.rb--;
	}
	while (move.ra < 0 && move.rb < 0)
	{
		rrr(a, b);
		move.ra++;
		move.rb++;
	}
	rotate_a(a, move.ra);
	rotate_b(b, move.rb);
}
