/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 16:56:10 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:24 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Ist rank zwischen previous und current einzufuegen?
** Behandelt auch den Kreisuebergang Maximum -> Minimum. */
static int	insertion_before(int previous, int current, int rank)
{
	if (previous < current)
		return (previous < rank && rank < current);
	return (rank > previous || rank < current);
}

/* Sucht den Einfuegeplatz fuer rank in zyklisch sortiertem A.
** Ergebnis: kuerzeste Rotation (+ra oder -rra).
** A wird hier noch nicht veraendert. */
static int	target_rota(t_stack *a, int rank)
{
	t_stack	*last;
	int		index;
	int		size;

	size = calc_size(a);
	if (size <= 1)
		return (0);
	last = a;
	while (last->next)
		last = last->next;
	index = 0;
	while (a)
	{
		if (insertion_before(last->rank, a->rank, rank))
			return (calc_rota_pos(index, size));
		last = a;
		a = a->next;
		index++;
	}
	return (0);
}

/* Berechnet die Kosten einer Rotationskombination.
** Bei weniger Operationen wird die bisher beste ersetzt.
** Bei Gleichstand gewinnt die kuerzere Gesamtstrecke. */
static void	check_move(t_sort_move *best, int a_steps, int b_steps)
{
	t_sort_move	move;

	move.ra = a_steps;
	move.rb = b_steps;
	move.cost = move_cost(a_steps, b_steps);
	if (move.cost < best->cost
		|| (move.cost == best->cost
			&& abs_steps(move.ra) + abs_steps(move.rb)
			< abs_steps(best->ra) + abs_steps(best->rb)))
		*best = move;
}

/* Probiert fuer A und B beide Drehrichtungen aus.
** Damit koennen rr und rrr auch laengere Einzelwege
** zu einer guenstigeren Gesamtkombination machen. */
static void	check_directions(t_sort_move *best, int *positions, int *sizes)
{
	check_move(best, positions[0], positions[1]);
	check_move(best, positions[0], positions[1] - sizes[1]);
	check_move(best, positions[0] - sizes[0], positions[1]);
	check_move(best, positions[0] - sizes[0], positions[1] - sizes[1]);
}

/* Vergleicht fuer jeden Kandidaten aus B alle Rotationsrichtungen.
** A bleibt dabei zyklisch sortiert. Keine Operation wird ausgefuehrt;
** do_move() dreht spaeter, insert_cheapest() fuehrt pa aus. */
t_sort_move	cheapest_move(t_stack *a, t_stack *b)
{
	t_sort_move	best;
	int			sizes[2];
	int			positions[2];

	sizes[0] = calc_size(a);
	sizes[1] = calc_size(b);
	best.cost = INT_MAX;
	positions[1] = 0;
	while (b)
	{
		positions[0] = target_rota(a, b->rank);
		if (positions[0] < 0)
			positions[0] += sizes[0];
		check_directions(&best, positions, sizes);
		b = b->next;
		positions[1]++;
	}
	return (best);
}
