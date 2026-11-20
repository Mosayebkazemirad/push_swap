/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 10:09:54 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:21 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Ein gemeinsamer, funktionslokaler static Zustand fuer Bench und
** Optimizer; keine globale Variable. Er bleibt bis Programmende da. */
t_ps_bench	*ps_bench_data(void)
{
	static t_ps_bench	bench;

	return (&bench);
}

/* Jede Sortierung beginnt mit leeren Zaehlern. */
void	ps_bench_begin(int enabled)
{
	t_ps_bench	*bench;
	int			i;

	bench = ps_bench_data();
	bench->enabled = enabled;
	bench->optimizer_on = 0;
	bench->pending_len = 0;
	bench->total = 0;
	i = 0;
	while (i < 11)
		bench->count[i++] = 0;
}

/* Disorder und ausgewaehlter Algorithmus stehen vor der ersten OP fest. */
void	ps_bench_set(double disorder, int strategy, int adaptive)
{
	t_ps_bench	*bench;

	bench = ps_bench_data();
	if (!bench->enabled)
		return ;
	bench->disorder = disorder;
	bench->strategy = strategy;
	bench->adaptive = adaptive;
}

/* Reihenfolge der elf erlaubten Operationen. Andere Texte zaehlen nicht. */
int	ps_op_kind(const char *operation)
{
	const char	*names[11] = {"sa\n", "sb\n", "ss\n", "pa\n",
		"pb\n", "ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	int			i;

	i = 0;
	while (i < 11)
	{
		if (same_word(operation, names[i]))
			return (i);
		i++;
	}
	return (-1);
}

/* Zaehlt nur direkt ausgegebene OPs, keine gepufferten Roh-Befehle.
** Der Optimizer benutzt beim Ausgeben ps_opt_write() statt hierher
** zurueckzuspringen. Die Summe entspricht der Checker-Eingabe. */
void	ps_bench_record(const char *operation)
{
	t_ps_bench	*bench;
	int			kind;

	bench = ps_bench_data();
	if (!bench->enabled)
		return ;
	kind = ps_op_kind(operation);
	if (kind < 0)
		return ;
	bench->count[kind]++;
	bench->total++;
}
