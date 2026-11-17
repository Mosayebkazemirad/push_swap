/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_opt_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:23:06 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:33 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Nur der Complex-Zweig aktiviert die Ausgabeoptimierung. */
void	ps_opt_begin(t_stack *a)
{
	t_ps_bench	*bench;

	(void)a;
	bench = ps_bench_data();
	bench->optimizer_on = 1;
	bench->pending_len = 0;
}

/* Schreibt am Ende der Complex-Sortierung alle Rest-OPs.
** Vorher bleibt der Checker-Ausgabestrom eventuell noch gepuffert.
** a wird nur fuer die gemeinsame Funktionssignatur uebergeben. */
void	ps_opt_finish(t_stack *a)
{
	t_ps_bench	*bench;

	(void)a;
	bench = ps_bench_data();
	if (!bench->optimizer_on)
		return ;
	ps_opt_flush(bench);
	bench->optimizer_on = 0;
}

/* Nur unabhaengige Einzel-Stack-OPs sind frei verschiebbar. */
static int	can_buffer(int kind)
{
	return (kind == 0 || kind == 1 || kind == 5
		|| kind == 6 || kind == 8 || kind == 9);
}

/* Pufferung nur im aktiven Complex-Modus.
** pa/pb oder Doppel-OPs sind eine sichere Blockgrenze: erst alle
** ausstehenden Einzel-OPs drucken, dann die aktuelle OP normal.
** Ist der Puffer voll, wird ebenfalls vorher geleert. */
int	ps_opt_capture(const char *op)
{
	t_ps_bench	*bench;
	int			kind;

	bench = ps_bench_data();
	if (!bench->optimizer_on)
		return (0);
	kind = ps_op_kind(op);
	if (kind < 0 || !can_buffer(kind))
	{
		ps_opt_flush(bench);
		return (0);
	}
	if (bench->pending_len == PS_OPT_BLOCK)
		ps_opt_flush(bench);
	bench->pending[bench->pending_len++] = (unsigned char)kind;
	return (1);
}
