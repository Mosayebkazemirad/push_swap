/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:48:46 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:45 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Erzwungene Strategie hat Vorrang vor der Adaptive-Auswahl.
** Adaptive: unter 20 % Simple, unter 50 % Medium, sonst Complex.
** Der Vergleich nutzt den exakten Disorder-Wert, nicht die Rundung. */
static int	select_algo(const char *mode, double disorder)
{
	if (same_word(mode, "--simple"))
		return (1);
	if (same_word(mode, "--medium"))
		return (2);
	if (same_word(mode, "--complex"))
		return (3);
	if (disorder < 0.2)
		return (1);
	if (disorder < 0.5)
		return (2);
	return (3);
}

/* Der gewaehlte Weg ist fuer Sortierung und Bench derselbe. */
static void	run_strategy(t_stack **a, t_stack **b, int strategy)
{
	if (strategy == 1)
		simple_ranked(a, b);
	else if (strategy == 2)
		medium_ranked(a, b);
	else
		complex_ranked(a, b);
}

/* Gemeinsamer Einstieg fuer alle Strategien.
** Ranking und Disorder werden nur einmal berechnet.
** Die Schnellpruefung vermeidet unnoetige Sortierarbeit. */
void	sort_stack(t_stack **a, t_stack **b, const char *mode)
{
	double	disorder;
	int		strategy;

	if (!a || !b || !*a)
		return ;
	get_ranked(*a);
	disorder = calc_disorder(*a);
	strategy = select_algo(mode, disorder);
	ps_bench_set(disorder, strategy,
		!mode || same_word(mode, "--adaptive"));
	if (quick_check(a, b))
		return ;
	run_strategy(a, b, strategy);
}
