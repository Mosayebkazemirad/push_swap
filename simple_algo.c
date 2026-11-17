/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:12:34 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:41 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Fallback ohne malloc: kleinsten noch fehlenden Rang suchen,
** nach B schieben und anschliessend alles zurueckholen.
** Benoetigt einen leeren Stack B beim Start. */
static void	selection_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	rank;
	int	pos;

	size = calc_size(*a);
	rank = 0;
	while (rank < size)
	{
		pos = calc_rank_pos(*a, rank);
		rotate_a(a, calc_rota_pos(pos, calc_size(*a)));
		pb(a, b);
		rank++;
	}
	while (*b)
		pa(a, b);
}

/* Simple behaelt die LIS in A und fuegt den Rest guenstig ein.
** Ohne Operationslimit; nur bei malloc-Fehler wird die alte
** Selection-Sort-Variante als speicherfreier Fallback genutzt. */
/*

*/
void	simple_ranked(t_stack **a, t_stack **b)
{
	if (!sort_greedy(a, b, 0, 0))
		selection_sort(a, b);
}
