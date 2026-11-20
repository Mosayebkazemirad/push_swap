/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   sort_small.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 20:56:14 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:54:50 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sonderfall fuer hoechstens fuenf Elemente.
** Kleinste Raenge nach B, verbleibende drei sortieren,
** danach alle Werte nach A zurueckholen. */

static int	sort_small(t_stack **a, t_stack **b)
{
	int	n;
	int	rank;
	int	pos;

	n = calc_size(*a);
	if (n > 5)
		return (0);
	if (n == 2 && (*a)->rank > (*a)->next->rank)
		sa(a);
	rank = 0;
	while (n > 3 && rank < n - 3)
	{
		pos = calc_rank_pos(*a, rank);
		rotate_a(a, calc_rota_pos(pos, calc_size(*a)));
		pb(a, b);
		rank++;
	}
	if (n >= 3)
		sort_three_a(a);
	while (*b)
		pa(a, b);
	return (1);
}

/* Vergleicht auch das letzte mit dem ersten Element.
** Genau ein Rangabstieg bedeutet eine zyklisch sortierte Folge,
** die nur noch bis Rang 0 rotiert werden muss. */

static int	cyclic_sorted(t_stack *a)
{
	t_stack	*head;
	int		breaks;

	head = a;
	breaks = 0;
	while (a->next)
	{
		if (a->rank > a->next->rank)
			breaks++;
		a = a->next;
	}
	if (a->rank > head->rank)
		breaks++;
	return (breaks == 1);
}

/* Sucht die erste Abweichung vom erwarteten Rang an dieser Stelle.
** Nur bei genau zwei falschen Positionen kommt ein Tausch infrage. */

static int	first_bad_position(t_stack *a)
{
	int	position;
	int	first;
	int	wrong;

	first = -1;
	wrong = 0;
	position = 0;
	while (a)
	{
		if (a->rank != position)
		{
			if (first == -1)
				first = position;
			wrong++;
		}
		position++;
		a = a->next;
	}
	if (wrong != 2)
		return (-1);
	return (first);
}

/* Prueft, ob zwei benachbarte Raenge vertauscht sind.
** Dann reicht: zur Stelle drehen, sa, zurueckdrehen. */

static int	check_one_swap(t_stack **a)
{
	t_stack	*node;
	int		first;
	int		rotate;

	first = first_bad_position(*a);
	if (first < 0)
		return (0);
	node = *a;
	rotate = first;
	while (rotate-- > 0)
		node = node->next;
	if (!node->next || node->rank != first + 1
			|| node->next->rank != first)
	return (0);
	rotate = calc_rota_pos(first, calc_size(*a));
	rotate_a(a, rotate);
	sa(a);
	rotate_a(a, -rotate);
	return (1);
}

/* Gemeinsame Abkuerzung vor den grossen Algorithmen.
** Sortiert, zyklisch sortiert, ein Swap oder <=5 Werte?
** 1 = fertig; 0 = Hauptstrategie wird noch gebraucht. */

int	quick_check(t_stack **a, t_stack **b)
{
	t_stack	*scan;
	int		pos;

	if (is_sorted(*a))
		return (1);
	if (!cyclic_sorted(*a))
	{
		if (calc_size(*a) > 3 && check_one_swap(a))
			return (1);
		return (sort_small(a, b));
	}
	scan = *a;
	pos = 0;
	while (scan && scan->rank != 0)
	{
		pos++;
		scan = scan->next;
	}
	rotate_a(a, calc_rota_pos(pos, calc_size(*a)));
	return (1);
}
